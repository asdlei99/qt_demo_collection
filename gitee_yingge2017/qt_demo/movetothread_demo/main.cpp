#include "mainwindow.h"

#include <QApplication>
#include <qthread.h>
#include <qdebug.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug()<<"main:"<<QThread::currentThreadId();
#if 0
    MainWindow w;
    w.show();
#endif

    QThread td;
    EventTask et;
    et.moveToThread(&td);
    td.start();

    return a.exec();
}
