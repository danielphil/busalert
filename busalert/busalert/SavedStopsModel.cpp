#include "SavedStopsModel.h"
#include <QSettings>

SavedStopsModel::SavedStopsModel(
    QObject* parent
) :
    QAbstractListModel(parent)
{
    Restore();
}

int SavedStopsModel::rowCount(const QModelIndex& /*parent*/) const {
    return m_stops.size();
}

QVariant SavedStopsModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= int(m_stops.size())) {
        return QVariant();
    }

    switch (role) {
    case Qt::DisplayRole: {
        const Item& item = m_stops[index.row()];
        QString text;
        if (!item.IsValid) {
            text += "! ";
        }
        text += item.Name;
        return text;
    }
    default:
        return QVariant();
    }
}

void SavedStopsModel::AddStop(const QString& stop_id, const QString& name) {
    Maybe<int> index = FindIndexForStop(stop_id);

    if (index.HasValue()) {
        // We're replacing an existing item
        m_stops[index.Value()] = Item(name, stop_id);
        const QModelIndex model_index = createIndex(index.Value(), 0);
        emit dataChanged(model_index, model_index);
    } else {
        beginInsertRows(QModelIndex(), m_stops.size(), m_stops.size());
        m_stops.push_back(Item(name, stop_id));
        endInsertRows();
    }

    Save();
}

void SavedStopsModel::RemoveStop(const QString& stop_id) {
    Maybe<int> index = FindIndexForStop(stop_id);

    if (index.HasValue()) {
        beginRemoveRows(QModelIndex(), index.Value(), index.Value());
        m_stops.erase(m_stops.begin() + index.Value());
        endRemoveRows();
    }

    Save();
}

QString SavedStopsModel::StopIdForIndex(int index) const {
    return m_stops.at(index).Id;
}

bool SavedStopsModel::IsStopValid(int index) const {
    return m_stops.at(index).IsValid;
}

Maybe<int> SavedStopsModel::FindIndexForStop(const QString& stop_id) const {
    const auto it = std::find_if(
        m_stops.begin(),
        m_stops.end(),
        [&stop_id] (const Item& item) {
            return item.Id == stop_id;
        }
    );

    if (it == m_stops.end()) {
        return Maybe<int>();
    } else {
        return it - m_stops.begin();
    }
}

void SavedStopsModel::Save() {
    QSettings settings;
    settings.beginWriteArray("saved_stops", m_stops.size());
    for (unsigned int i = 0; i < m_stops.size(); i++) {
        settings.setArrayIndex(i);
        settings.setValue("stop_id", m_stops.at(i).Id);
        settings.setValue("stop_name", m_stops.at(i).Name);
    }
    settings.endArray();
}

void SavedStopsModel::Restore() {
    QSettings settings;
    const int size = settings.beginReadArray("saved_stops");
    for (int i = 0; i < size; i++) {
        settings.setArrayIndex(i);
        QString stop_id = settings.value("stop_id").toString();
        QString stop_name = settings.value("stop_name").toString();
        m_stops.push_back(Item(stop_name, stop_id));
    }
    settings.endArray();
}

void SavedStopsModel::UpdateStopList(const Buslib::BusStops& new_stops) {
    for (unsigned int i = 0; i < m_stops.size(); i++) {
        Item& item = m_stops[i];
        item.IsValid = new_stops.IsValidStopId(item.Id);
        const QModelIndex model_index = createIndex(i, 0);
        emit dataChanged(model_index, model_index);
    }
}
