#include "mainwindow.h"
#include <qtranslator.h>
#include <QApplication>
#include <qdebug.h>
#include <qfile.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug()<<QCoreApplication::applicationFilePath()
           <<QCoreApplication::applicationDirPath();


#if 0
    QString qmPath = QCoreApplication::applicationDirPath() +
            "/en.qm";

    qDebug()<<"qmPath:"<<qmPath;
    if(false == QFile::exists(qmPath) ){
        qDebug()<<"qmPath not exist.";
    }

    QTranslator translator(0);
    if(false == translator.load(qmPath,".")){
        qDebug()<<"load failed.";
    }
    a.installTranslator(&translator);
#endif

    MainWindow w;
    w.show();


    return a.exec();
}
