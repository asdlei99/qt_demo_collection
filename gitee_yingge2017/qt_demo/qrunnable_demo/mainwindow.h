#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include  <qrunnable.h>
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
public slots:
    void slotRevData(const int&data);
private:
    void singleTask();
    void multiTask();
private:
    Ui::MainWindow *ui;
};

class TaskRunnable:public QObject ,public QRunnable{
    Q_OBJECT
public:
    TaskRunnable(const int &runnableId):m_runnableId(runnableId){}
signals:
    void sigSendData(const int &data);
protected:
    void run()override;
private:
    int m_runnableId;
};

#endif // MAINWINDOW_H
