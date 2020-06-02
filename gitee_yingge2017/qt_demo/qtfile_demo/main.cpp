#include <QCoreApplication>
#include <qdebug.h>
#include <qfile.h>
#include <qdir.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //获取程序当前目录
    qDebug()<<QCoreApplication::applicationDirPath();
    qDebug()<<QCoreApplication::applicationFilePath();
    qDebug()<<QCoreApplication::applicationPid();


    return a.exec();
}
