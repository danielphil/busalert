#pragma once
#include <QByteArray>
#include <string>

namespace Buslib
{
    class TopologyId
    {
    public:
        bool FromData(const QByteArray& json_data);
        std::string Id() const;

    private:
        std::string m_topology_id;
    };
}
