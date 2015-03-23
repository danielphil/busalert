#pragma once
#include <QByteArray>

namespace Buslib
{
    namespace Tools
    {
        void WriteJsonToFile(const QByteArray& data, const QString& path);
    }
}
