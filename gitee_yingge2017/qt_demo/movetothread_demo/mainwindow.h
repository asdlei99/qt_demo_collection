#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qobject.h>
#include <qmap.h>

class QThread;

namespace Ui {
class MainWindow;
}
//任务类,不是用Qt事件循环，自己维护一个while循环
class Task:public QObject{
    Q_OBJECT
public:
    Task();
    ~Task();
    void setStop(){m_bDestory = true;}
signals:
    void sigSendData(const int& data);
public slots:
    void slotStartTask();
private:
    bool m_bDestory;
};

/**
 * @brief The MainWindow class
 * 使用Qt事件循环
 */
class EventTask:public QObject{
    Q_OBJECT
public:
    EventTask();
    ~EventTask();
protected:
    void timerEvent(QTimerEvent *event);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void slotStart();
    void slotStop();
    void slotRevData(const int &data);
private:
    Ui::MainWindow *ui;
    QThread *m_pThread;
    Task *m_pTask;
    QMap<QThread*,Task*> m_threadTaskMap;

};


#endif // MAINWINDOW_H
