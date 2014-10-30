#include "mainwindow.h"

#include <QApplication>
#include <QtWebKitWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Anomaly");
    a.setApplicationVersion("0.0.0");

    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalStorageEnabled,true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard,true);

    MainWindow w;
    w.show();

    return a.exec();
}
