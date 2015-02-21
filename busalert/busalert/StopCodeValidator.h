#pragma once
#include "buslib/BusStops.h"
#include <QRegExpValidator>
#include <memory>

class StopCodeValidator : public QRegExpValidator
{
    Q_OBJECT
public:
    explicit StopCodeValidator(const Buslib::BusStops& stops, QObject *parent = 0);

    virtual State validate(QString& input, int& pos) const;

private:
    class StopTreeNode
    {
    public:
        explicit StopTreeNode();
        bool AddString(const QString& number_string);
        QValidator::State ValidateString(const QString& number_string) const;

    private:
        std::vector<std::shared_ptr<StopTreeNode>> m_children;
        bool m_has_children;
    };

    Buslib::BusStops m_stops;
    std::shared_ptr<StopTreeNode> m_root_node;
};
