/*
 * Qt驱动是在MySQL lib的基础上封装而成的，所以运行的时候需要使用相应的库。
 * 在x64系统下，编译该代码的时候需要把libmysql.dll文件复制到D:\Qt\Qt5.12.0\5.12.0\mingw73_64\bin目录下。
 * 在x86系统中需要下载相应的库文件。
 *
*/

#include <QCoreApplication>
#include <qapplication.h>
#include <qsqldatabase.h>
#include <qdebug.h>

#include "sqlconnecter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    //    QCoreApplication a(argc, argv);

    qDebug()<<"sql demo main.";
    qDebug()<<"drivers:"<<QSqlDatabase::drivers();

    SqlConnecter s;

    //    return 0;
    return a.exec();
}
