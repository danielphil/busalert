#include "buslib/Tools.h"
#include <QDebug>
#include <QFile>
#include <QJsonDocument>

namespace Buslib
{
    namespace Tools
    {
        void WriteJsonToFile(const QByteArray& data, const QString& path) {
            QFile output_file(path);
            if (!output_file.open(QIODevice::WriteOnly)) {
                qDebug() << "Failed to open file" << path;
                return;
            }
            QJsonDocument json_document = QJsonDocument::fromBinaryData(data);
            output_file.write(json_document.toBinaryData());
            output_file.close();
        }
    }
}
