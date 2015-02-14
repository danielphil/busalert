#include "buslib/DataDownloader.h"
#include "buslib/MyBusTracker.h"
#include "buslib/TopologyId.h"
#include <QDir>
#include <QStandardPaths>
#include <QJsonDocument>

namespace Buslib
{
    DataDownloader::DataDownloader(
        const std::string& api_key
    ) :
        m_bus_tracker(new Buslib::MyBusTracker(api_key)),
        m_download_in_progress(false)
    {
        QString cache_location = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
        QDir cache_directory(cache_location);
        if (!cache_directory.exists()) {
            cache_directory.mkpath(cache_location);
        }

        m_topology_id_cache_location = cache_location + "/topology_id.txt";
        m_stop_cache_location = cache_location + "/stops.json";
        m_service_cache_location = cache_location + "/services.json";
    }

    bool DataDownloader::DownloadRequired() const {
        return
            !QFile(m_topology_id_cache_location).exists() ||
            !QFile(m_stop_cache_location).exists() ||
            !QFile(m_service_cache_location).exists();
    }

    void DataDownloader::DownloadNewData(
        const std::function<void (bool)>& download_complete_callback
    ) {
        if (m_download_in_progress) {
            // Don't do anything if we're already trying to get the data
            return;
        }

        m_download_complete_callback = download_complete_callback;

        Maybe<std::string> last_topology_id;
        QFile topology_id_file(m_topology_id_cache_location);
        if (topology_id_file.exists()) {
            topology_id_file.open(QIODevice::ReadOnly);
            TopologyId id;
            if (id.FromData(topology_id_file.readAll())) {
                last_topology_id = id.Id();
            } else {
                qDebug() << "Failed to read topology ID from cached file";
            }
            topology_id_file.close();
        }

        m_download_in_progress = true;

        m_tasks = {
            [=] () { DownloadTopologyId(last_topology_id); },
            [=] () { DownloadStopData(); },
            [=] () { DownloadServiceData(); }
        };

        RunNextTask();
    }

    BusStops DataDownloader::GetStopsData() const {
        QFile stops_file(m_stop_cache_location);
        stops_file.open(QIODevice::ReadOnly);
        BusStops stops;
        stops.FromData(stops_file.readAll());
        stops_file.close();
        return stops;
    }

    void DataDownloader::DownloadComplete(bool has_data_changed) {
        m_tasks.clear();
        m_download_in_progress = false;

        if (has_data_changed) {
            SaveDataToFile(m_topology_id_cache_location, m_new_topology_id_data);
            qDebug() << "New data to load from MyBusTracker.";
        } else {
            qDebug() << "No new data.";
        }

        m_download_complete_callback(has_data_changed);
    }

    void DataDownloader::DownloadError(Buslib::Error error) {
        qDebug() << "Error while downloading:" << error.ErrorMessage().c_str();
        m_tasks.clear();
        m_download_in_progress = false;
    }

    void DataDownloader::RunNextTask() {
        if (m_tasks.empty()) {
            DownloadComplete(true);
        } else {
            auto next_task = m_tasks.front();
            m_tasks.pop_front();
            next_task();
        }
    }

    void DataDownloader::DownloadTopologyId(const Maybe<std::string>& last_topology_id) {
        m_bus_tracker->GetTopologyId([=] (QByteArray current_id_data) {
            TopologyId id;
            if (!id.FromData(current_id_data)) {
                qDebug() << "Failed to obtain topology ID from JSON!";
                DownloadComplete(false);
                return;
            }

            if (last_topology_id.HasValue() && last_topology_id.Value() == id.Id()) {
                // If the last ID still matches, we don't need to download anything
                DownloadComplete(false);
            } else {
                m_new_topology_id_data = current_id_data;
                RunNextTask();
            }
        }, std::bind(&DataDownloader::DownloadError, this, std::placeholders::_1));
    }

    void DataDownloader::DownloadStopData() {
        m_bus_tracker->GetBusStops([this] (QByteArray stop_data) {
            SaveDataToFile(m_stop_cache_location, stop_data);
            RunNextTask();
        }, std::bind(&DataDownloader::DownloadError, this, std::placeholders::_1));
    }

    void DataDownloader::DownloadServiceData() {
        m_bus_tracker->GetServices([this] (QByteArray service_data) {
            SaveDataToFile(m_service_cache_location, service_data);
            RunNextTask();
        }, std::bind(&DataDownloader::DownloadError, this, std::placeholders::_1));
    }

    void DataDownloader::SaveDataToFile(const QString& path, const QByteArray& data) {
        QFile file(path);
        file.open(QIODevice::WriteOnly);
        file.write(QJsonDocument::fromJson(data).toJson());
        file.close();
    }
}
