#include <QPushButton>
#include <QtNetwork>
#include <QString>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tcpServer(nullptr),
    tcpSocket(nullptr),
    udpSocket(nullptr)
{
    ui->setupUi(this);
    ui->m_startTCPServer->setDisabled(false);
    ui->m_stopTCPServer->setDisabled(true);
    ui->m_unbindUdp->setDisabled(true);

    connect(ui->m_clearConsole, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), [this]{
        ui->m_console->clear();
    });

    connect(ui->m_startTCPServer, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, &MainWindow::startTCPServer);
    connect(ui->m_stopTCPServer, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, &MainWindow::stopTCPServer);
    connect(ui->m_tcpConnect, static_cast<void(QPushButton::*)(bool)>(&QPushButton::clicked), this, &MainWindow::connectTCPServer);
    connect(ui->m_tcpSendMsg, static_cast<void(QPushButton::*)(bool)>(&QPushButton::clicked), this, &MainWindow::sendTcpMessage);
    connect(ui->m_tcpClientMsg, &QLineEdit::returnPressed, this, &MainWindow::sendTcpMessage);

    connect(ui->m_bindUdp, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, &MainWindow::bindUdp);
    connect(ui->m_unbindUdp, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, &MainWindow::unbindUdp);
    connect(ui->m_sendUDPMessage, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, &MainWindow::sendUdpMessage);
    connect(ui->m_udpMessage, &QLineEdit::returnPressed, this, &MainWindow::sendUdpMessage);
}

MainWindow::~MainWindow()
{
    delete ui;

    if (udpSocket)
        delete udpSocket;
}

void MainWindow::startTCPServer()
{
    QString address = ui->m_tcpInterface->text();
    quint16 port = ui->m_tcpPort->text().toInt();
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
            ui->m_console->append(QString("%1:%2 says: %3").arg(socket->peerAddress().toString()).arg(socket->peerPort()).arg(str));
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

        ui->m_console->append(QString("TCP Sever stopped"));
        ui->m_startTCPServer->setDisabled(false);
        ui->m_stopTCPServer->setDisabled(true);
    }
}

void MainWindow::connectTCPServer()
{
    if (tcpSocket == nullptr)
    {
        tcpSocket = new QTcpSocket();
        tcpSocket->connectToHost(QHostAddress(ui->m_tcpServerAddress->text()), ui->m_tcpServerPort->text().toInt());
        tcpSocket->waitForConnected();
        ui->m_tcpConnect->setText("Disconnect");
    }
    else
    {
        tcpSocket->flush();
        tcpSocket->close();
        delete tcpSocket;
        tcpSocket = nullptr;
        ui->m_tcpConnect->setText("Connect");
    }
}

void MainWindow::sendTcpMessage()
{
    if (tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        QString msg = ui->m_tcpClientMsg->text();
        tcpSocket->write(msg.toUtf8());
        tcpSocket->waitForBytesWritten();
        ui->m_console->append(QString("Sent [%1] to %2:%3").arg(msg).arg(tcpSocket->peerAddress().toString()).arg(tcpSocket->peerPort()));
    }
}

void MainWindow::bindUdp()
{
    udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress(ui->m_udpAddress->text()), ui->m_udpPort->text().toInt());
    ui->m_console->append(QString("Bind UDP receiver at %1:%2").arg(ui->m_udpAddress->text()).arg(ui->m_udpPort->text().toInt()));
    ui->m_bindUdp->setDisabled(true);
    ui->m_unbindUdp->setDisabled(false);

    connect(udpSocket, &QUdpSocket::readyRead, [this]{
        while(udpSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            QHostAddress remoteAddress;
            quint16 remotePort;
            datagram.resize(udpSocket->pendingDatagramSize());
            udpSocket->readDatagram(datagram.data(), datagram.size(), &remoteAddress, &remotePort);
            ui->m_console->append(QString("%2:%3 says: %1").arg(QString(datagram)).arg(remoteAddress.toString()).arg(remotePort));
        }
    });
}

void MainWindow::unbindUdp()
{
    if(udpSocket)
    {
        udpSocket->close();
        delete udpSocket;
        udpSocket = nullptr;
        ui->m_bindUdp->setDisabled(false);
    }
}

void MainWindow::sendUdpMessage()
{
    QString msg = ui->m_udpMessage->text();
    QString address = ui->m_udpRemoteAddress->text();
    quint16 port = ui->m_udpRemotePort->text().toInt();

    udpSocket->writeDatagram(msg.toUtf8(), QHostAddress(address), port);
    udpSocket->flush();
    ui->m_console->append(QString("Sent [%1] to %2:%3").arg(msg).arg(address).arg(port));
}
