#ifndef STOPARRIVALSWINDOW_H
#define STOPARRIVALSWINDOW_H

#include <QWidget>
#include "buslib/MyBusTracker.h"
#include "buslib/StopTimes.h"
#include <QTimer>

namespace Ui {
class StopArrivalsWindow;
}

class StopArrivalsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StopArrivalsWindow(
        const QString& stop_id,
        QWidget *parent = 0
    );
    ~StopArrivalsWindow();

private:
    void BuildList(const Buslib::StopTimes&);
    void ClearLayout(QLayout* layout, bool deleteWidgets = true);
    void RequestBusTimes();

    Ui::StopArrivalsWindow *ui;
    Buslib::MyBusTracker m_bus_tracker;
    QTimer m_update_timer;
    const QString m_stop_id;
};

#endif // STOPARRIVALSWINDOW_H
