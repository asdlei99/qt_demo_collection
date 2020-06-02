#include <QCoreApplication>
#include <qdebug.h>
#include <qelapsedtimer.h>

#include "secretprocess.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    qDebug()<<"kill_process start.";

    QElapsedTimer et;
    et.start();
    while(et.elapsed() < 1000);

    secretprocess::doSecretPrpcess(NULL);

//    qDebug()<<"kill_process end.";

    exit(0);

    return a.exec();
}
