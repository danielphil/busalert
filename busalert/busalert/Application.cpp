#include "busalert/Application.h"
#include "busalert/ApiKey.h"
#include <QSplashScreen>
#include <QPixmap>
#include <QMessageBox>

Application::Application(
) :
    m_downloader(ApiKey::MyBusTrackerKey)
{
}

void Application::Start() {
    if (m_downloader.DownloadRequired()) {
        // Need to download the bus data before we can do anything else
        m_splash_screen.reset(new QSplashScreen(QPixmap(":/bstopd.gif")));
        m_splash_screen->show();
        m_splash_screen->showMessage("Now downloading service information...");
        m_downloader.DownloadNewData(
            [this] (bool) {
                ShowWindows();
                m_splash_screen->finish(&m_stops_dialog);
            },
            [this] () {
                m_splash_screen->hide();
                OnDownloadError();
            }
        );
    } else {
        // Show the application straight away
        ShowWindows();
    }
}

void Application::ShowWindows() {
    m_main_window.reset(new MainWindow(&m_downloader, &m_saved_stops_model));
    m_main_window->show();
}

void Application::OnDownloadError() {
    std::unique_ptr<QMessageBox> alert(new QMessageBox());
    alert->setText("Unable to download stop information");
    alert->setInformativeText("Please check your Internet connection and restart the application.");
    alert->setIcon(QMessageBox::Critical);
    alert->exec();
}
