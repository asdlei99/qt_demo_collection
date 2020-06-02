#include "mainwindow.h"
#include <QApplication>
#include <qdebug.h>
#include     <qthread.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    qDebug()<<"main:"<<QThread::currentThreadId();

    Producer p;
    Customer c;

    p.start();
    c.start();

    p.wait();
    c.wait();

    return a.exec();
}
