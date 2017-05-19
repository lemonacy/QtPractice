#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    QUdpSocket *udpSocket;

private slots:
    void startTCPServer();
    void stopTCPServer();
    void connectTCPServer();
    void sendTcpMessage();

    void bindUdp();
    void unbindUdp();
    void sendUdpMessage();
};

#endif // MAINWINDOW_H
