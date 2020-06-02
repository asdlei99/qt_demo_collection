#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qobject.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

class QTcpSocket;
class TcpClient:public QObject{
    Q_OBJECT
public:
    TcpClient();
private slots:
    void slotCennected();
    void slotDisconnected();
private:
    bool m_bStop;
    QTcpSocket *m_pSocket;
};

#endif // MAINWINDOW_H
