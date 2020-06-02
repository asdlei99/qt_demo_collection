#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <qtcpsocket.h>
#include <qudpsocket.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newConnect();
    void readyRead();
    void slotUdpReadyRead();
private:
    Ui::MainWindow *ui;
    QTcpServer *_tcpServer;
    QTcpSocket *_clientTcpSocket;
    QUdpSocket *_udpSocket;
};

#endif // MAINWINDOW_H
