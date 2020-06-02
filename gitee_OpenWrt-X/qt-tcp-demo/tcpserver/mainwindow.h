#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QTimer>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void init();
 private slots:
    void on_send_clicked();
    void newListen();
    void acceptConnection();
    void displayError(QAbstractSocket::SocketError);
private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    QTimer *timer;
};

#endif // MAINWINDOW_H
