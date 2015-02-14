#pragma once
#include "buslib/Arrival.h"
#include <QJsonObject>
#include <string>
#include <vector>

namespace Buslib
{
    class StopTimes
    {
    public:
        bool FromData(const QByteArray& json_data);
        const std::vector<Buslib::Arrival>& Arrivals() const;
        std::vector<Buslib::Arrival> ArrivalsInTimeOrder() const;

    private:
        std::vector<Buslib::Arrival> m_arrivals;
    };
}
