#include "buslib/StopTimes.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

namespace Buslib
{
    bool StopTimes::FromData(const QByteArray& json_data) {
        QJsonDocument json = QJsonDocument::fromJson(json_data);
        QJsonArray bus_times = json.object()["busTimes"].toArray();
        for (QJsonValue time : bus_times) {
            QJsonObject json_object(time.toObject());
            QString service = json_object["mnemoService"].toString();
            for (QJsonValue time_data : json_object["timeDatas"].toArray()) {
                QString destination = time_data.toObject()["nameDest"].toString();
                int minutes = time_data.toObject()["minutes"].toInt();
                QString time = time_data.toObject()["time"].toString();
                QString reliability = time_data.toObject()["reliability"].toString();
                bool diverted = reliability == "V";
                m_arrivals.push_back(Arrival(service, destination, minutes, time, diverted));
            }
        }
        return true;
    }

    const std::vector<Arrival>& StopTimes::Arrivals() const {
        return m_arrivals;
    }

    std::vector<Buslib::Arrival> StopTimes::ArrivalsInTimeOrder() const {
        std::vector<Buslib::Arrival> sorted_arrivals(m_arrivals);
        std::sort(
            sorted_arrivals.begin(),
            sorted_arrivals.end(),
            [] (const Arrival& l, const Arrival& r) {
                if (l.Minutes() == r.Minutes()) {
                    bool l_is_int, r_is_int;
                    const int l_as_int = l.ServiceName().toInt(&l_is_int);
                    const int r_as_int = r.ServiceName().toInt(&r_is_int);

                    if (l_is_int && !r_is_int) {
                        // Numbers before strings (l < r)
                        return true;
                    } else if (!l_is_int && r_is_int) {
                        // Numbers before strings (r >= l)
                        return false;
                    } else if (l_is_int && r_is_int) {
                        // Compare numeric value
                        return l_as_int < r_as_int;
                    } else {
                        // Compare as strings
                        return l.ServiceName() < r.ServiceName();
                    }
                } else {
                    return l.Minutes() < r.Minutes();
                }
            }
        );
        return sorted_arrivals;
    }
}
