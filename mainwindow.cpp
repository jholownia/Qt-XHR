#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "networkaccessmanager.h"

#include <QtWebKitWidgets/QWebView>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWebView* webView = new QWebView;

    QNetworkAccessManager* oldManager = webView->page()->networkAccessManager();
    NetworkAccessManager* newManager = new NetworkAccessManager(oldManager, this);
    webView->page()->setNetworkAccessManager(newManager);

    webView->setUrl(QUrl("http://test"));

    this->setCentralWidget(webView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
