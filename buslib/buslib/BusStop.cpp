#include "buslib/BusStop.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

namespace Buslib
{
    bool BusStop::FromObject(const QJsonObject& json_object) {
        m_name = json_object["name"].toString();
        m_stop_id = json_object["stopId"].toString();

        return true;
    }

    const QString& BusStop::Name() const {
        return m_name;
    }

    const QString& BusStop::StopId() const {
        return m_stop_id;
    }
}
