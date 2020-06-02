#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qthread.h>
#include <qsemaphore.h>
#include <qdebug.h>
#include <qdatetime.h>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QSemaphore ProducerSe(1);
QSemaphore CustomerSe;

void Producer::run(){
    for(int i = 0; i < 1000; ++i) {
        ProducerSe.acquire();
        int num = QRandomGenerator::global()->bounded(5);
        qDebug()<<"Producer:"<<QThread::currentThreadId()
                  <<",release source count:"<<num<<"|"
               <<QDateTime::currentDateTime().toString(Qt::ISODateWithMs);
        CustomerSe.release(num);
        QThread::msleep(3000);
    }
}

void Customer::run(){
    for(int i = 0; i < 1000; ++i) {
        CustomerSe.acquire() ;
        qDebug()<<"Customer:"<<(int*)QThread::currentThreadId()<<"|"
               <<QDateTime::currentDateTime().toString(Qt::ISODateWithMs);
        ProducerSe.release();
    }
}
