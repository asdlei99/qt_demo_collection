#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qmutex.h>
#include   <qdebug.h>
#include <qwaitcondition.h>


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

QMutex mutex;
QWaitCondition wcBufferFull;
QWaitCondition wcBufferEmpty;

int bufferCount = 0;
const int ConMaxCount = 100;

void Producer::run()
{
//    while(true){
    for(int i = 0 ; i < 10000; ++i){
        mutex.lock();
        if(bufferCount == ConMaxCount){
            wcBufferFull.wait(&mutex);
        }
        mutex.unlock();

        mutex.lock();
        ++bufferCount;
        ++bufferCount;
        qDebug()<<"Producer:"<<QThread::currentThreadId()
               <<":"<<bufferCount;
        wcBufferEmpty.wakeAll();
        mutex.unlock();

        QThread::msleep(500);
    }
}

void Customer::run()
{
//    while(true){
    for(int i = 0 ; i < 10000; ++i){
        mutex.lock();
        if(bufferCount == 0){
            wcBufferEmpty.wait(&mutex);
        }
        mutex.unlock();

        mutex.lock();
        --bufferCount;
        qDebug()<<"Custmer: "<<QThread::currentThreadId()
                <<":"<<bufferCount;
        wcBufferFull.wakeAll();
        mutex.unlock();

        QThread::msleep(300);
    }
}
