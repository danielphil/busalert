#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "busalert/SavedStopsModel.h"
#include "buslib/DataDownloader.h"
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QItemSelection>

class Application;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(
        Buslib::DataDownloader* data_downloader,
        SavedStopsModel* saved_stops,
        Application* app,
        QWidget *parent = 0
    );
    ~MainWindow();

private slots:
    void on_addStop_clicked();

    void on_removeStop_clicked();

private:
    void ClearLayout(QLayout* layout, bool deleteWidgets = true);
    void SelectionChanged();

    Ui::MainWindow *ui;
    Buslib::DataDownloader* m_data_downloader;
    SavedStopsModel* const m_saved_stops_model;
};

#endif // MAINWINDOW_H
