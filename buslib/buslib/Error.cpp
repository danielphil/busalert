#include "buslib/Error.h"

namespace Buslib
{
    Error::Error(
        const std::string& error_message,
        QNetworkReply::NetworkError network_error
    ) : m_error_message(error_message), m_network_error(network_error) {
    }

    QNetworkReply::NetworkError Error::NetworkError() const {
        return m_network_error;
    }

    const std::string& Error::ErrorMessage() const {
        return m_error_message;
    }
}
