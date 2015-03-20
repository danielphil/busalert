#ifndef STOPARRIVALSWINDOW_H
#define STOPARRIVALSWINDOW_H

#include <QWidget>
#include "buslib/MyBusTracker.h"
#include "buslib/StopTimes.h"
#include <QTimer>
#include <QStatusBar>

namespace Ui {
class StopArrivalsWindow;
}

class StopArrivalsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StopArrivalsWindow(
        const QString& stop_id,
        QStatusBar* status_bar,
        QWidget *parent = 0
    );
    ~StopArrivalsWindow();

private:
    void BuildList(const Buslib::StopTimes&);
    void DisplayError();

    void ClearLayout(QLayout* layout, bool deleteWidgets = true);
    void RequestBusTimes();

    Ui::StopArrivalsWindow *ui;
    Buslib::MyBusTracker m_bus_tracker;
    QTimer m_update_timer;
    const QString m_stop_id;
    QStatusBar* m_status_bar;
};

#endif // STOPARRIVALSWINDOW_H
