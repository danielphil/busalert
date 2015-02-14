#include "buslib/TopologyId.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

namespace Buslib
{
    std::string TopologyId::Id() const {
        return m_topology_id;
    }

    bool TopologyId::FromData(const QByteArray& json_data) {
        QJsonDocument json = QJsonDocument::fromJson(QString(json_data).toUtf8());
        if (json.isNull()) {
            qDebug() << "Failed to create the JSON document!";
            return false;
        }

        if (!json.isObject()) {
            qDebug() << "Expected JSON object!";
            return false;
        }

        const QJsonObject& obj = json.object();
        m_topology_id = obj["topoId"].toString().toStdString();

        return true;
    }
}
