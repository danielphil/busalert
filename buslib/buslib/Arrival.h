#pragma once
#include <QString>

namespace Buslib
{
    class Arrival
    {
    public:
        Arrival(
            const QString& service_name,
            const QString& destination,
            int minutes,
            const QString& time
        );

        const QString& Destination() const;
        int Minutes() const;
        const QString& Time() const;
        const QString& ServiceName() const;

    private:
        QString m_destination;
        int m_minutes;
        QString m_time;
        QString m_service;
    };
}
