#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include   <qthread.h>
#include     <qdebug.h>
#include <qthreadpool.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug()<<"mainwindow thread id:"<<QThread::currentThreadId();

    //    ui->setupUi(this);

    // singleTask();
    multiTask();
}

void MainWindow::slotRevData(const int&data){
    qDebug()<<"mainwindow thread id:"<<QThread::currentThreadId()
           <<"MainWindow rev data:"<<data;
}

void MainWindow::singleTask()
{
    TaskRunnable *tr = new TaskRunnable(0);
    connect(tr,&TaskRunnable::sigSendData,
            this,&MainWindow::slotRevData);
    tr->setAutoDelete(true);

    QThreadPool::globalInstance()->start(tr);
}

void MainWindow::multiTask()
{
    QThreadPool::globalInstance()->setMaxThreadCount(9);

    for(int i = 0; i < 20; ++i){
        TaskRunnable *tr = new TaskRunnable(i);
//        connect(tr,&TaskRunnable::sigSendData,
//                this,&MainWindow::slotRevData);
        tr->setAutoDelete(true);

        QThreadPool::globalInstance()->start(tr);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void TaskRunnable::run()
{
#if 1
    for(int i = 0; i < 5; ++i)    {
        qDebug()<<"thread id:"<<QThread::currentThreadId()
               <<"|"<<QDateTime::currentDateTime().toString(Qt::ISODateWithMs);
        QThread::msleep(200);
    }
    emit sigSendData(100);

    qDebug()<<"TaskRunnable run return";
#endif

#if 0
    qDebug()<<"thread id:"<<QThread::currentThreadId()
           <<"|"<<QDateTime::currentDateTime().toString(Qt::ISODateWithMs);
    QThread::msleep(200);
#endif


}
