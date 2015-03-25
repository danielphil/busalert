#pragma once
#include "Maybe.h"
#include "buslib/BusStops.h"
#include <QAbstractListModel>

class SavedStopsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    SavedStopsModel(QObject* parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role) const;

    void AddStop(const QString& stop_id, const QString& name);
    void RemoveStop(const QString& stop_id);
    QString StopIdForIndex(int index) const;
    bool IsStopValid(int index) const;

    void UpdateStopList(const Buslib::BusStops&);

private:
    class Item
    {
    public:
        Item(
            const QString& name, const QString& id
        ) :
            Name(name),
            Id(id),
            IsValid(true)
        {
        }

        QString Name;
        QString Id;
        bool IsValid;
    };

    Maybe<int> FindIndexForStop(const QString& stop_id) const;
    void Save();
    void Restore();

    // Stop name to stop ID
    std::vector<Item> m_stops;
};
