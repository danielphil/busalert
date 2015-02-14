#pragma once
#include "Maybe.h"
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

private:
    Maybe<int> FindIndexForStop(const QString& stop_id) const;
    void Save();
    void Restore();

    // Stop name to stop ID
    std::vector<std::pair<QString, QString>> m_stops;
};
