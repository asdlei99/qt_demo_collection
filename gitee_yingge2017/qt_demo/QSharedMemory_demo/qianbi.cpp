#include "qianbi.h"

#include <qsharedmemory.h>
#include <qdebug.h>
#include <qbuffer.h>

Qianbi::Qianbi(QObject *parent):
    QObject (parent)
{
    startTimer(1000);
}

void Qianbi::timerEvent(QTimerEvent *event)
{
    //设置key
    QSharedMemory sm("sm_demo");
    //固定
    if(false == sm.attach(QSharedMemory::ReadOnly)){
        qDebug()<<"attach failed."<<sm.errorString();
        return;
    }
    //加锁
    if(false == sm.lock()){
        qDebug()<<"lock failed."<<sm.errorString();
        return;
    }

    QBuffer buf;
    buf.open(QIODevice::WriteOnly);
    buf.write((char*)sm.data());
    buf.close();

    //解锁
    if(false == sm.unlock()){
        qDebug()<<"unlock failed."<<sm.errorString();
        return;
    }
    qDebug()<<"read from shared memory:"<<buf.data();

}
