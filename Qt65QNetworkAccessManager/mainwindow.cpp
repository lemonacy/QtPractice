#include "mainwindow.h"
#include "networker.h"
#include <QDebug>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    NetWorker * worker = NetWorker::instance();
//    connect(worker, &NetWorker::finished, this, &MainWindow::finished);
//    worker->get("http://a2.xgsdk.com:18888/isAlive");
}

MainWindow::~MainWindow()
{

}

void MainWindow::finished(QNetworkReply *reply)
{
    qDebug() << reply;
    QJsonParseError error;
    QJsonDocument json = QJsonDocument::fromJson(reply->readAll(), &error);
    if (error.error == QJsonParseError::NoError)
    {
        QVariantMap data = json.toVariant().toMap();
        qDebug() << data;
        QString appName = data[QLatin1String("application")].toString();
        bool isAlive = data[QLatin1String("isAlive")].toBool();
        qDebug() << QString("%1 is %2").arg(appName).arg(isAlive);
    }
    reply->deleteLater();
}
