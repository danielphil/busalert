#include "busalert/MainWindow.h"

#include "busalert/Application.h"
#include "busalert/EditStopDialog.h"
#include "busalert/StopArrivalsWindow.h"
#include "busalert/NoStopSelectedWidget.h"
#include "ui_MainWindow.h"
#include <QIcon>
#include <QMessageBox>

MainWindow::MainWindow(
    Buslib::DataDownloader* data_downloader,
    SavedStopsModel* saved_stops,
    Application* app,
    QWidget* parent
) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_data_downloader(data_downloader),
    m_saved_stops_model(saved_stops)
{
    ui->setupUi(this);

    ui->stopsList->setModel(m_saved_stops_model);
    QObject::connect(
        ui->stopsList->selectionModel(),
        &QItemSelectionModel::selectionChanged,
        std::bind(&MainWindow::SelectionChanged, this)
    );

    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    QAction *aboutAction = helpMenu->addAction(tr("&About"));
    QObject::connect(aboutAction, &QAction::triggered, [app] () { app->ShowAboutBox(); });
    menuBar()->addMenu(helpMenu);

    SelectionChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ClearLayout(QLayout* layout, bool deleteWidgets) {
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

void MainWindow::on_addStop_clicked()
{
    EditStopDialog dialog(m_data_downloader, this);
    dialog.setWindowFlags(Qt::Sheet);
    if (dialog.exec() == QDialog::Accepted) {
        m_saved_stops_model->AddStop(dialog.GetStopId(), dialog.GetStopName());
    }
}

void MainWindow::SelectionChanged() {
    statusBar()->clearMessage();

    QModelIndexList selected_indicies = ui->stopsList->selectionModel()->selectedIndexes();

    ClearLayout(ui->bus_times_layout, true);
    if (selected_indicies.empty()) {
        ui->bus_times_layout->addWidget(new NoStopSelectedWidget());
    } else {
        const QString stop_id = m_saved_stops_model->StopIdForIndex(selected_indicies.at(0).row());
        ui->bus_times_layout->addWidget(new StopArrivalsWindow(stop_id, statusBar()));
    }
}

void MainWindow::on_removeStop_clicked()
{
    QModelIndexList selected_indicies = ui->stopsList->selectionModel()->selectedIndexes();

    if (!selected_indicies.empty()) {
        const QString stop_id = m_saved_stops_model->StopIdForIndex(selected_indicies.at(0).row());
        m_saved_stops_model->RemoveStop(stop_id);
    }
}
