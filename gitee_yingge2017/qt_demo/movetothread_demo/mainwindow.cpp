#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qdebug.h>
#include  <qthread.h>
#include  <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //    connect(ui->pushButtonStart,&QPushButton::click,
    //            this,&MainWindow::slotStart);
    //    connect(ui->pushButtonStop,&QPushButton::click,
    //            this,&MainWindow::slotStop);
#if 0
    connect(ui->pushButtonStart,&QPushButton::clicked,
            [&]{
        m_pTask = new Task;
        m_pThread = new QThread;
        //将任务移动到子线程中
        m_pTask->moveToThread(m_pThread);

        //终止线程时要调用Task deleteLater函数
        connect(m_pThread,&QThread::finished,
                m_pTask,&QObject::deleteLater);
        //开启任务执行槽函数,当线程启动，started信号将被发送
        connect(m_pThread,&QThread::started,
                m_pTask,&Task::slotStartTask);
        //启动线程
        m_pThread->start();

    });
    //停止按钮
    connect(ui->pushButtonStop,&QPushButton::clicked,
            [&]{
        if(m_pThread->isRunning()){
            qDebug()<<"pushButtonStop clicked";
            m_pTask->setStop();
            m_pThread->quit();
            m_pThread->wait();
            qDebug()<<"MainWindow stop thread,wait return.";
        }
    });
#endif
#if 1
    connect(ui->pushButtonStart,&QPushButton::clicked,
            [&]{
        m_pTask = new Task;
        m_pThread = new QThread;
        //将任务移动到子线程中
        m_pTask->moveToThread(m_pThread);

        //终止线程时要调用Task deleteLater函数
        connect(m_pThread,&QThread::finished,
                m_pTask,&QObject::deleteLater);
        //开启任务执行槽函数,当线程启动，started信号将被发送
        connect(m_pThread,&QThread::started,
                m_pTask,&Task::slotStartTask);
        //启动线程
        m_pThread->start();

        m_threadTaskMap.insert(m_pThread,m_pTask);
        ui->label_num->setText(QString::number(m_threadTaskMap.size()));
    });
    //停止按钮
    connect(ui->pushButtonStop,&QPushButton::clicked,
            [&]{
        if(m_threadTaskMap.isEmpty()){
            return ;
        }
        QThread *td = m_threadTaskMap.firstKey();
        Task *tk = (Task*)m_threadTaskMap.value(td);
        m_threadTaskMap.remove(td);
        ui->label_num->setText(QString::number(m_threadTaskMap.size()));

        if(td->isRunning()){
            qDebug()<<"pushButtonStop clicked";
            tk->setStop();
            td->quit();
            td->wait();
            qDebug()<<"MainWindow stop thread,wait return.";
        }

    });
#endif

}

MainWindow::~MainWindow()
{
    delete ui;

    if(m_pTask){
        delete m_pTask;
        m_pTask = nullptr;
    }

    if(m_pThread){
        delete m_pThread;
        m_pThread = nullptr;
    }
}

void MainWindow::slotStart()
{

}

void MainWindow::slotStop()
{

}

void MainWindow::slotRevData(const int &data)
{
    qDebug()<<"MainWindow get thread id:"<<data;
}


Task::Task()
    :m_bDestory(false)
{
    //不起作用
    //当任务类销毁时，停止循环
    connect(this,&QObject::destroyed,
            [&]{
        m_bDestory = true;
    });
}

Task::~Task()
{

}

void Task::slotStartTask()
{
    while(true){
        if(m_bDestory){
            break;
        }
        qDebug()<<"Task slotStartTask,thread id:"
               <<QThread::currentThreadId()
                <<"|"<<QDateTime::currentDateTime().toString(Qt::ISODateWithMs);
        QThread::sleep(1);
    }
}

EventTask::EventTask()
{
    startTimer(500);
}

EventTask::~EventTask()
{

}

void EventTask::timerEvent(QTimerEvent *event)
{
    qDebug()<<"EventTask slotStartTask,thread id:"
           <<QThread::currentThreadId()
            <<"|"<<QDateTime::currentDateTime().toString(Qt::ISODateWithMs);
}
