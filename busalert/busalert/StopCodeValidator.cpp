#include "StopCodeValidator.h"
#include <QDebug>

StopCodeValidator::StopCodeValidator(
    const Buslib::BusStops& stops,
    QObject *parent
) :
    QRegExpValidator(parent),
    m_stops(stops)
{
    setRegExp(QRegExp("\\d*"));
    m_root_node = std::make_shared<StopTreeNode>();
    for (const auto& pair : m_stops.Stops()) {
        const QString& stop_code = pair.first;
        if (!m_root_node->AddString(stop_code)) {
            qDebug() << "Failed to add stop code" << stop_code;
        }
    }
}

StopCodeValidator::State StopCodeValidator::validate(QString& input, int& pos) const {
    // First filter on numbers only
    auto state = QRegExpValidator::validate(input, pos);
    if (state != StopCodeValidator::Acceptable) {
        return state;
    }

    if (!m_root_node) {
        // No available stops
        return StopCodeValidator::Invalid;
    } else {
        return m_root_node->ValidateString(input);
    }
}

StopCodeValidator::StopTreeNode::StopTreeNode(
) :
    m_children(10, nullptr),
    m_has_children(false)
{
}

bool StopCodeValidator::StopTreeNode::AddString(const QString& number_string) {
    if (number_string.length() == 0) {
        return true;
    }

    QString first_digit = number_string.at(0);
    bool ok;
    int number = first_digit.toInt(&ok);
    if (!ok) {
        return false;
    }

    if (m_children.at(number) == nullptr) {
        m_children[number] = std::make_shared<StopTreeNode>();
        m_has_children = true;
    }

    QString remaining_digits = number_string.mid(1);
    return m_children.at(number)->AddString(remaining_digits);
}

QValidator::State StopCodeValidator::StopTreeNode::ValidateString(const QString& number_string) const {
    if (number_string.length() == 0) {
        if (m_has_children) {
            // We have children, so there's more characters the user can type
            return QValidator::Intermediate;
        } else {
            // No children, so we've found a complete stop code
            return QValidator::Acceptable;
        }
    }

    QString first_digit = number_string.at(0);
    int number = first_digit.toInt();

    if (m_children.at(number) == nullptr) {
        // No child for this number
        return QValidator::Invalid;
    }

    QString remaining_digits = number_string.mid(1);
    return m_children.at(number)->ValidateString(remaining_digits);
}
