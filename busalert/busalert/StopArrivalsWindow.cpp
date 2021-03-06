#include "StopArrivalsWindow.h"
#include "ui_StopArrivalsWindow.h"
#include <QLabel>
#include <QProgressBar>
#include <QTableView>
#include "busalert/ApiKey.h"
#include "buslib/StopTimes.h"

StopArrivalsWindow::StopArrivalsWindow(
    const QString& stop_id,
    bool is_valid,
    QStatusBar* status_bar,
    QWidget* parent
) :
    QWidget(parent),
    ui(new Ui::StopArrivalsWindow),
    m_bus_tracker(ApiKey::MyBusTrackerKey),
    m_stop_id(stop_id),
    m_status_bar(status_bar)
{
    ui->setupUi(this);

    if (is_valid) {
        m_update_timer.setSingleShot(true);
        m_update_timer.setInterval(60 * 1000);

        QObject::connect(&m_update_timer, &QTimer::timeout, [this] () {
            m_status_bar->showMessage("Updating...");
            RequestBusTimes();
        });

        QVBoxLayout* vertical_layout = new QVBoxLayout;
        vertical_layout->addStretch();

        QLabel* message = new QLabel;
        message->setText("Loading arrivals...");
        message->setTextFormat(Qt::PlainText);
        message->setAlignment(Qt::AlignHCenter);
        vertical_layout->addWidget(message);

        QProgressBar* progress_bar = new QProgressBar;
        progress_bar->setMinimum(0);
        progress_bar->setMaximum(0);
        vertical_layout->addWidget(progress_bar);

        vertical_layout->addStretch();

        ui->scrollAreaWidgetContents->setLayout(vertical_layout);

        RequestBusTimes();
    } else {
        DisplayInvalidStop();
    }
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
    m_arrivals_model.ClearArrivals();
    for (const Buslib::Arrival& arrival : stop_times.ArrivalsInTimeOrder()) {
        m_arrivals_model.AddArrival(arrival);
    }

    QTableView* table_view = new QTableView;
    table_view->setShowGrid(false);
    table_view->setAlternatingRowColors(true);
    table_view->setCornerButtonEnabled(false);
    table_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_view->setSelectionMode(QAbstractItemView::NoSelection);
    table_view->verticalHeader()->setVisible(false);
    table_view->horizontalHeader()->setStretchLastSection(true);
    table_view->setModel(&m_arrivals_model);
    table_view->setFocusPolicy(Qt::NoFocus);
    vertical_layout->addWidget(table_view);
    ui->scrollAreaWidgetContents->setLayout(vertical_layout);
}

void StopArrivalsWindow::DisplayError() {
    if (ui->scrollAreaWidgetContents->layout()) {
        ClearLayout(ui->scrollAreaWidgetContents->layout());
        delete ui->scrollAreaWidgetContents->layout();
    }

    QVBoxLayout* vertical_layout = new QVBoxLayout;
    QLabel* error_message = new QLabel;
    error_message->setScaledContents(true);
    error_message->setText("An error occurred. Please check your Internet connection.");
    error_message->setTextFormat(Qt::PlainText);
    error_message->setWordWrap(true);
    error_message->setAlignment(Qt::AlignCenter);
    vertical_layout->addWidget(error_message);

    ui->scrollAreaWidgetContents->setLayout(vertical_layout);
}

void StopArrivalsWindow::DisplayInvalidStop() {
    if (ui->scrollAreaWidgetContents->layout()) {
        ClearLayout(ui->scrollAreaWidgetContents->layout());
        delete ui->scrollAreaWidgetContents->layout();
    }

    QVBoxLayout* vertical_layout = new QVBoxLayout;
    QLabel* error_message = new QLabel;
    error_message->setScaledContents(true);
    error_message->setText("The selected stop is no longer available.");
    error_message->setTextFormat(Qt::PlainText);
    error_message->setWordWrap(true);
    error_message->setAlignment(Qt::AlignCenter);
    vertical_layout->addWidget(error_message);

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
            QString last_update_message = "Last update at ";
            last_update_message += QDateTime::currentDateTime().toString();
            m_status_bar->showMessage(last_update_message);
            Buslib::StopTimes stop_times;
            stop_times.FromData(data);
            BuildList(stop_times);
            m_update_timer.start();
        },
        [this] (Buslib::Error /*error*/) {
            m_status_bar->clearMessage();
            DisplayError();
        }
    );
}
