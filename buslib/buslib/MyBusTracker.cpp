#include "buslib/MyBusTracker.h"
#include "buslib/TopologyId.h"
#include <sstream>
#include <iomanip>
#include <QDateTime>
#include <QCryptographicHash>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

namespace Buslib
{
    MyBusTracker::MyBusTracker(
        const std::string& api_key
    ) :
        m_api_key(api_key)
    {
    }

    void MyBusTracker::GetTopologyId(
        const SuccessCallback success_callback,
        const ErrorCallback error_callback
    ) {
        BeginRequest(GetUrl("getTopoId"), error_callback, [=] (const QByteArray& data) {
            success_callback(data);
        });
    }

    void MyBusTracker::GetBusStops(
        const SuccessCallback success_callback,
        const ErrorCallback error_callback
    ) {
        BeginRequest(GetUrl("getBusStops"), error_callback, [=] (const QByteArray& data) {
            success_callback(data);
        });
    }

    void MyBusTracker::GetServices(
        const SuccessCallback success_callback,
        const ErrorCallback error_callback
    ) {
        BeginRequest(GetUrl("getServices"), error_callback, [=] (const QByteArray& data) {
            success_callback(data);
        });
    }

    void MyBusTracker::GetBusTimes(
        const std::string& stop_id,
        const SuccessCallback success_callback,
        const ErrorCallback error_callback
    ) {
        QUrl url = GetUrl("getBusTimes", { { "stopId", stop_id } });
        BeginRequest(url, error_callback, success_callback);
    }

    std::string MyBusTracker::GetHashedKey(
        const std::string& api_key, const QDateTime& datetime
    ) {
        std::stringstream str;
        str << api_key;

        const QDate date = datetime.date();
        str << std::setfill('0') << std::setw(4) << date.year();
        str << std::setw(2) << date.month();
        str << std::setw(2) << date.day();

        const QTime time = datetime.time();
        str << std::setw(2) << time.hour();

        const std::string key_to_hash = str.str();

        const QByteArray hash = QCryptographicHash::hash(key_to_hash.c_str(), QCryptographicHash::Md5);
        return hash.toHex().constData();
    }

    QUrl MyBusTracker::GetUrl(
        const std::string& function_name,
        const std::map<std::string, std::string>& additional_params
    ) const {
        QUrlQuery query;
        query.addQueryItem("module", "json");
        query.addQueryItem("function", function_name.c_str());
        query.addQueryItem("key", GetHashedKey(m_api_key).c_str());
        for (auto pair : additional_params) {
            query.addQueryItem(pair.first.c_str(), pair.second.c_str());
        }

        QUrl url("http://ws.mybustracker.co.uk/");
        url.setQuery(query);

        return url;
    }

    void MyBusTracker::BeginRequest(
        const QUrl& url,
        std::function<void (Error)> user_error_callback,
        std::function<void (const QByteArray&)> on_success
    ) {
        QNetworkReply* reply = m_network_access_manager.get(QNetworkRequest(url));

        QObject::connect(
            reply,
            &QNetworkReply::finished,
            [=] () {
                QByteArray data = reply->readAll();
                QNetworkReply::NetworkError error = reply->error();
                if (error != QNetworkReply::NoError) {
                    user_error_callback(Buslib::Error(QString(data).toStdString(), error));
                } else {
                    on_success(data);
                }
                reply->deleteLater();
            }
        );
    }
}
