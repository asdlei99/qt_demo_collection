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
protected:
    void init();
    void newTCPConnect();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
private slots:
    void revData();
    void display(QAbstractSocket::SocketError);
};

#endif // MAINWINDOW_H
