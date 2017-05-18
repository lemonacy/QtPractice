#include <QPushButton>
#include <QtNetwork>
#include <QString>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tcpServer(nullptr),
    udpReceiver(nullptr)
{
    ui->setupUi(this);
    ui->m_startTCPServer->setDisabled(false);
    ui->m_stopTCPServer->setDisabled(true);
    ui->m_unbindUdp->setDisabled(true);

    connect(ui->m_startTCPServer, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, &MainWindow::startTCPServer);
    connect(ui->m_stopTCPServer, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, &MainWindow::stopTCPServer);

    connect(ui->m_bindUdp, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, &MainWindow::bindUdp);
    connect(ui->m_unbindUdp, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, &MainWindow::unbindUdp);
    connect(ui->m_sendUDPMessage, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, &MainWindow::sendUdpMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startTCPServer()
{
    QString address("10.20.72.124");
    quint16 port = 56666;
    tcpServer = new QTcpServer();
    tcpServer->listen(QHostAddress(address), port);
    ui->m_startTCPServer->setDisabled(true);
    ui->m_stopTCPServer->setDisabled(false);
    ui->m_console->append(QString("TCP server started at %1:%2").arg(address).arg(port));
    connect(tcpServer, &QTcpServer::newConnection, [this]{
        QTcpSocket *socket = tcpServer->nextPendingConnection();
        ui->m_console->append(QString("%1:%2 connected").arg(socket->peerAddress().toString()).arg(socket->peerPort()));
        connect(socket, &QTcpSocket::readyRead, [socket, this]{
            QString str = socket->readAll();
            ui->m_console->append(QString("%1:%2 says:%3").arg(socket->peerAddress().toString()).arg(socket->peerPort()).arg(str));
            socket->write(QString("Yes? %1").arg(str).toStdString().c_str());
        });
        connect(socket, &QTcpSocket::disconnected, [socket, this]{
            ui->m_console->append(QString("%1:%2 disconnected").arg(socket->peerAddress().toString()).arg(socket->peerPort()));
        });
    });
}

void MainWindow::stopTCPServer()
{
    if(tcpServer)
    {
        tcpServer->close();
        delete tcpServer;
        tcpServer = nullptr;

        ui->m_console->append(QString("TCP Sever stopped\n"));
        ui->m_startTCPServer->setDisabled(false);
        ui->m_stopTCPServer->setDisabled(true);
    }
}

void MainWindow::bindUdp()
{
    udpReceiver = new QUdpSocket();
    udpReceiver->bind(QHostAddress(ui->m_udpAddress->text()), ui->m_udpPort->text().toInt());
    ui->m_console->append(QString("Bind UDP receiver at %1:%2").arg(ui->m_udpAddress->text()).arg(ui->m_udpPort->text().toInt()));
    ui->m_bindUdp->setDisabled(true);
    ui->m_unbindUdp->setDisabled(false);

    connect(udpReceiver, &QUdpSocket::readyRead, [this]{
        QString msg = udpReceiver->readAll();
        ui->m_console->append(QString("Received [%1] from %2:%3").arg(msg).arg(udpReceiver->localAddress().toString()).arg(udpReceiver->localPort()));
    });
}

void MainWindow::unbindUdp()
{
    if(udpReceiver)
    {
        udpReceiver->close();
        delete udpReceiver;
        udpReceiver = nullptr;
        ui->m_bindUdp->setDisabled(false);
    }
}

void MainWindow::sendUdpMessage()
{
    QUdpSocket sender;
    QString msg = ui->m_udpMessage->text();
    QString address = ui->m_udpRemoteAddress->text();
    quint16 port = ui->m_udpRemotePort->text().toInt();

    sender.writeDatagram(msg.toUtf8(), QHostAddress(address), port);
    ui->m_console->append(QString("Send [%1] to %2:%3").arg(msg).arg(address).arg(port));
}
