#include "busalert/ArrivalsModel.h"
#include <QDebug>

ArrivalsModel::ArrivalsModel(
    QObject* parent
) :
    QAbstractTableModel(parent)
{
}

int ArrivalsModel::rowCount(const QModelIndex& /*parent*/) const {
    return m_arrivals.size();
}

int ArrivalsModel::columnCount(const QModelIndex& /*parent*/) const {
    return 3;
}

QVariant ArrivalsModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() ||
        index.column() < 0 ||
        index.row() < 0 ||
        index.column() >= columnCount() ||
        index.row() >= int(m_arrivals.size())
    ) {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
        switch (index.column()) {
            case 0:
            case 1:
                return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    } if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0:
                return QVariant(m_arrivals.at(index.row()).ServiceName());
            case 1:
                return QVariant(m_arrivals.at(index.row()).Destination());
            case 2: {
                    const Buslib::Arrival& arrival = m_arrivals.at(index.row());
                    if (arrival.IsDiverted()) {
                        return "Diverted";
                    } else if (arrival.IsEstimated()) {
                        return QString("Estimated in ") + QString::number(arrival.Minutes()) + " minutes";
                    } else {
                        return QString::number(arrival.Minutes()) + " minutes";
                    }
                }
        }
    }

    return QVariant();
}

QVariant ArrivalsModel::headerData(
    int section, Qt::Orientation orientation, int role
) const {
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) {
        return QAbstractTableModel::headerData(section, orientation, role);
    }

    switch (section) {
        case 0:
            return "Service";
        case 1:
            return "Destination";
        case 2:
            return "Arrival Time";
        default:
            return QVariant();
    }
}

void ArrivalsModel::AddArrival(const Buslib::Arrival& arrival) {
    beginInsertRows(QModelIndex(), m_arrivals.size(), m_arrivals.size());
    m_arrivals.push_back(arrival);
    endInsertRows();
}

void ArrivalsModel::ClearArrivals() {
    beginResetModel();
    m_arrivals.clear();
    endResetModel();
}
