#pragma once
#include "busalert/AvailableStopsDialog.h"
#include "busalert/MainWindow.h"
#include "buslib/DataDownloader.h"
#include <QSplashScreen>

class Application
{
public:
    Application();

    void Start();

private:
    void ShowWindows();
    void OnDownloadError();

    Buslib::DataDownloader m_downloader;
    std::unique_ptr<QSplashScreen> m_splash_screen;
    AvailableStopsDialog m_stops_dialog;
    std::unique_ptr<MainWindow> m_main_window;
    SavedStopsModel m_saved_stops_model;
};
