#include "busalert/Application.h"
#include "busalert/StopArrivalsWindow.h"
#include "buslib/MyBusTracker.h"
#include "buslib/DataDownloader.h"
#include "buslib/StopTimes.h"

#include <QApplication>
#include <QNetworkProxyFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);

    a.setOrganizationName("danielphil");
    a.setApplicationName("Edinburgh Bus Tracker");

    // Use system configured HTTP proxy server settings (if applicable)
    QNetworkProxyFactory::setUseSystemConfiguration(true);

    Application app;
    app.Start();

    return a.exec();
}
