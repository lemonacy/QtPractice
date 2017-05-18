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
    QUdpSocket *udpReceiver;
    QUdpSocket *udpSender;

private slots:
    void startTCPServer();
    void stopTCPServer();
    void bindUdp();
    void unbindUdp();
    void sendUdpMessage();
};

#endif // MAINWINDOW_H
