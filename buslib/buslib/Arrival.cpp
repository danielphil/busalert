#include "buslib/Arrival.h"

namespace Buslib
{
    Arrival::Arrival(
        const QString& service_name,
        const QString& destination,
        int minutes,
        const QString& time
    ) :
        m_destination(destination),
        m_minutes(minutes),
        m_time(time),
        m_service(service_name)
    {
    }

    const QString& Arrival::Destination() const {
        return m_destination;
    }

    int Arrival::Minutes() const {
        return m_minutes;
    }

    const QString& Arrival::Time() const {
        return m_time;
    }

    const QString& Arrival::ServiceName() const {
        return m_service;
    }
}
