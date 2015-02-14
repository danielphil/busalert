#pragma once
#include "Maybe.h"
#include <QNetworkReply>

namespace Buslib
{
    class Error {
    public:
        Error(const std::string& error_message, QNetworkReply::NetworkError = QNetworkReply::NoError);

        QNetworkReply::NetworkError NetworkError() const;
        const std::string& ErrorMessage() const;

    private:
        std::string m_error_message;
        QNetworkReply::NetworkError m_network_error;
    };
}
