#include "StopArrivalsWindow.h"
#include "ui_StopArrivalsWindow.h"
#include <QLabel>
#include "busalert/ApiKey.h"
#include "buslib/StopTimes.h"

StopArrivalsWindow::StopArrivalsWindow(
    const QString& stop_id,
    QWidget* parent
) :
    QWidget(parent),
    ui(new Ui::StopArrivalsWindow),
    m_bus_tracker(ApiKey::MyBusTrackerKey),
    m_stop_id(stop_id)
{
    ui->setupUi(this);

    m_update_timer.setSingleShot(true);
    m_update_timer.setInterval(60 * 1000);

    QObject::connect(&m_update_timer, &QTimer::timeout, [this] () {
        RequestBusTimes();
    });

    RequestBusTimes();
}

StopArrivalsWindow::~StopArrivalsWindow()
{
    delete ui;
}

void StopArrivalsWindow::BuildList(const Buslib::StopTimes& stop_times) {
    if (ui->scrollAreaWidgetContents->layout()) {
        ClearLayout(ui->scrollAreaWidgetContents->layout());
        delete ui->scrollAreaWidgetContents->layout();
    }

    QVBoxLayout* vertical_layout = new QVBoxLayout;
    for (const Buslib::Arrival& arrival : stop_times.ArrivalsInTimeOrder()) {
        QHBoxLayout* horizontal_layout = new QHBoxLayout;

        QLabel* bus_number = new QLabel;
        bus_number->setScaledContents(true);
        bus_number->setText(arrival.ServiceName());
        bus_number->setTextFormat(Qt::PlainText);
        bus_number->setFrameStyle(QFrame::Box);
        horizontal_layout->addWidget(bus_number);

        QLabel* destination = new QLabel;
        destination->setScaledContents(true);
        destination->setText(arrival.Destination());
        destination->setTextFormat(Qt::PlainText);
        horizontal_layout->addWidget(destination);

        horizontal_layout->addStretch();

        QLabel* arrival_time_label = new QLabel;
        arrival_time_label->setScaledContents(true);
        arrival_time_label->setText(QString::number(arrival.Minutes()) + " minutes");
        arrival_time_label->setTextFormat(Qt::PlainText);
        horizontal_layout->addWidget(arrival_time_label);

        vertical_layout->addLayout(horizontal_layout);
    }
    vertical_layout->addStretch();
    ui->scrollAreaWidgetContents->setLayout(vertical_layout);
}

void StopArrivalsWindow::ClearLayout(QLayout* layout, bool deleteWidgets) {
    // From http://stackoverflow.com/questions/4272196/qt-remove-all-widgets-from-layout
    while (QLayoutItem* item = layout->takeAt(0)) {
        if (deleteWidgets) {
            if (QWidget* widget = item->widget()) {
                delete widget;
            }
        }
        if (QLayout* childLayout = item->layout()) {
            ClearLayout(childLayout, deleteWidgets);
        }
        delete item;
    }
}

void StopArrivalsWindow::RequestBusTimes() {
    m_bus_tracker.GetBusTimes(
        m_stop_id.toStdString(),
        [this] (QByteArray data) {
            Buslib::StopTimes stop_times;
            stop_times.FromData(data);
            BuildList(stop_times);
            m_update_timer.start();
        },
        [] (Buslib::Error error) { qDebug() << "Something screwed up"; }
    );
}
