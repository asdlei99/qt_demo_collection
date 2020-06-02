#include <QCoreApplication>
#include <qthread.h>
#include <qdatetime.h>
#include <qdebug.h>
#include <QSharedMemory>

#include "qianbi.h"
#include "qianwritor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QianWritor w;
    Qianbi q;

    return a.exec();
}

