#pragma once
#include <QJsonObject>
#include <string>

namespace Buslib
{
    class BusStop
    {
    public:
        bool FromObject(const QJsonObject& json_object);

        const QString& Name() const;
        const QString& StopId() const;

    private:
        QString m_name;
        QString m_stop_id;
    };
}
