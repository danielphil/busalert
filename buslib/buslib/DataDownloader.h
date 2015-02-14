#pragma once
#include "buslib/BusStops.h"
#include "buslib/Error.h"
#include "buslib/MyBusTracker.h"
#include "Maybe.h"
#include <string>
#include <deque>

namespace Buslib
{
    class DataDownloader
    {
    public:
        DataDownloader(const std::string& api_key);

        bool DownloadRequired() const;
        void DownloadNewData(const std::function<void (bool)>& download_complete_callback);
        BusStops GetStopsData() const;

    private:
        void DownloadComplete(bool has_data_changed);
        void DownloadError(Buslib::Error error);

        void RunNextTask();

        void DownloadTopologyId(const Maybe<std::string>& last_topology_id);
        void DownloadStopData();
        void DownloadServiceData();

        void SaveDataToFile(const QString& path, const QByteArray& data);

        QString m_topology_id_cache_location;
        QString m_stop_cache_location;
        QString m_service_cache_location;

        std::unique_ptr<Buslib::MyBusTracker> m_bus_tracker;
        bool m_download_in_progress;
        QByteArray m_new_topology_id_data;

        std::deque<std::function<void ()>> m_tasks;

        std::function<void (bool)> m_download_complete_callback;
    };
}
