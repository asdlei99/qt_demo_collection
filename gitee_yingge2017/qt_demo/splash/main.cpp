#include "mainwindow.h"
#include <qdatetime.h>
#include <QApplication>
#include <qfile.h>
#include <qdebug.h>

/**
 * @brief qMain
 * @param argc
 * @param argv
 * argv[1]，ms,splash持续时间,范围是1000-10000毫秒。
 * argv[2], splash不显示到最前端，0不触发。
 * argv[3],ms,读取共享内存时间间隔,根据页面是否卡顿设置。默认200毫秒。
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString currentTimeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd:hh:mm:ss.zzz");

    SplashWidget *w = new SplashWidget;
    w->writeLog(QString("start|").append(currentTimeStr));

    //1.加载页面持续时长
    bool ok = false;
    int elapseMs = 0;
    if(argc >= 2 && *argv[1] != NULL){
        elapseMs = QString("%1").arg(argv[1]).toInt(&ok);
        //时间设置范围1000-10000毫秒
        if(ok){
            if((elapseMs > 20000) || (elapseMs < 1000)){
                elapseMs = 2000;
            }
        }else{
            elapseMs = 2000;
        }
    }else{
        //默认时间为2000毫秒
        elapseMs = 2000;
    }
    //2.显示到最前端
    if(argc >= 3 && *argv[2] != NULL){
        int value= QString(argv[2]).toInt();
        if(value != 0){
            w->setWindowFlags(w->windowFlags()|Qt:: WindowStaysOnTopHint);
        }
    }
    //3.读取共享内存时间间隔
    int smReadMs = 200;
    if(argc >= 4 && *argv[3] != NULL){
        smReadMs = QString("%1").arg(argv[3]).toInt(&ok);
    }
    w->setShareMemoryReadMs(smReadMs);

    w->setElapsedMs(elapseMs);
    w->move(-13,-13);
    w->show();

    //write log

    for(int i = 0; i < argc;i++){
        QString s = QString("argv:") + argv[i];
        w->writeLog(s);
    }

    QString elapseStr = QString("elapseMs:") +
            QString::number(elapseMs);
    w->writeLog(elapseStr);

    QString shareMemoryMsStr = QString("shareMemoryMs:") +
            QString::number(smReadMs);
    w->writeLog(shareMemoryMsStr);

    //程序退出
    QObject::connect(w,SIGNAL(sigQuit()),
                     &a,SLOT(quit()));

    return a.exec();
}
