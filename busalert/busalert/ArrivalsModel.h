#pragma once
#include "buslib/Arrival.h"
#include <QAbstractTableModel>

class ArrivalsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ArrivalsModel(QObject* parent = 0);

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex& index, int role) const;
    virtual QVariant headerData(
        int section,
        Qt::Orientation orientation,
        int role = Qt::DisplayRole
    ) const;

    void AddArrival(const Buslib::Arrival& arrival);

    void ClearArrivals();

private:
    std::vector<Buslib::Arrival> m_arrivals;
};
