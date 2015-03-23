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
            const QString& time,
            bool diverted,
            bool estimated_time
        );

        const QString& Destination() const;
        int Minutes() const;
        const QString& Time() const;
        const QString& ServiceName() const;
        bool IsDiverted() const;
        bool IsEstimated() const;

    private:
        QString m_destination;
        int m_minutes;
        QString m_time;
        QString m_service;
        bool m_diverted;
        bool m_is_estimated;
    };
}
