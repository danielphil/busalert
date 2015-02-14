#pragma once
#include "buslib/Error.h"
#include <string>
#include <QNetworkAccessManager>
#include <map>

namespace Buslib
{
    class MyBusTracker
    {
    public:
        MyBusTracker(const std::string& api_key);

        typedef std::function<void (QByteArray)> SuccessCallback;
        typedef std::function<void (Buslib::Error)> ErrorCallback;

        void GetTopologyId(
            const SuccessCallback success_callback,
            const ErrorCallback error_callback
        );

        void GetBusStops(
            const SuccessCallback success_callback,
            const ErrorCallback error_callback
        );

        void GetServices(
            const SuccessCallback success_callback,
            const ErrorCallback error_callback
        );

        void GetBusTimes(
            const std::string& stop_id,
            const SuccessCallback success_callback,
            const ErrorCallback error_callback
        );

        static std::string GetHashedKey(
            const std::string& api_key,
            const QDateTime& current_date_time = QDateTime::currentDateTimeUtc()
        );

    private:
        typedef std::map<std::string, std::string> QueryMap;

        QUrl GetUrl(
            const std::string& function_name,
            const QueryMap& additional_params = QueryMap()
        ) const;

        void BeginRequest(
            const QUrl& url,
            std::function<void (Error)> user_error_callback,
            std::function<void (const QByteArray&)> on_success
        );

        QNetworkAccessManager m_network_access_manager;
        std::string m_api_key;
    };
}
