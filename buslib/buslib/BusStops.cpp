#include "buslib/BusStops.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

namespace Buslib
{
    bool BusStops::FromData(const QByteArray& json_data) {
        QJsonDocument json = QJsonDocument::fromJson(json_data);
        if (json.isNull()) {
            qDebug() << "Failed to create the JSON document!";
            return false;
        }

        if (!json.isObject()) {
            qDebug() << "Expected JSON object!";
            return false;
        }

        const QJsonArray stops = json.object()["busStops"].toArray();
        for (QJsonValue value : stops) {
            BusStop stop;
            stop.FromObject(value.toObject());
            m_stops[stop.StopId()] = stop;
        }

        return true;
    }

    const std::map<QString, BusStop>& BusStops::Stops() const {
        return m_stops;
    }

    const BusStop& BusStops::GetStop(const QString& stop_id) const {
        return m_stops.at(stop_id);
    }

    bool BusStops::IsValidStopId(const QString& stop_id) const {
        return m_stops.find(stop_id) != m_stops.end();
    }
}
