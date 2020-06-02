#include "qianwritor.h"

#include <qdebug.h>
#include <qdatetime.h>

QianWritor::QianWritor(QObject *parent) :
    QObject(parent),
    m_sm(new QSharedMemory("sm_demo"))
{
    if(true == m_sm->isAttached()){
        m_sm->detach();
    }
    //设置空间
    if(false == m_sm->create(100)){
        qDebug()<<"create failed."<<m_sm->errorString();
        return;
    }

    startTimer(500);
}

QianWritor::~QianWritor()
{
    m_sm->deleteLater();
    m_sm = nullptr;
}

void QianWritor::timerEvent(QTimerEvent *e)
{
    if(false == m_sm->lock()){
        qDebug()<<"main lock failed."<<m_sm->errorString();
        return;
    }

    QString dtstr = QDateTime::currentDateTime().toString(Qt::ISODateWithMs);
    memcpy((char*)m_sm->data(),dtstr.toStdString().data(),m_sm->size());

    qDebug()<<"write data:"<<dtstr;

    if(false == m_sm->unlock()){
        qDebug()<<"main unlock failed."<<m_sm->errorString();
        return;
    }
}
