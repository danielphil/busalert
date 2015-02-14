#pragma once
#include "buslib/BusStop.h"
#include <QByteArray>
#include <string>
#include <map>

namespace Buslib
{
    class BusStops
    {
    public:
        bool FromData(const QByteArray& json_data);
        const std::map<QString, BusStop>& Stops() const;
        const BusStop& GetStop(const QString& stop_id) const;
        bool IsValidStopId(const QString& stop_id) const;

    private:
        std::map<QString, BusStop> m_stops;
    };
}
