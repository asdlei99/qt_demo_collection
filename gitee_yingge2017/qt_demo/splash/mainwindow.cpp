#include "mainwindow.h"

#include <QHBoxLayout>
#include <qdebug.h>
#include <qapplication.h>
#include <qfile.h>
#include <QTextStream>
#include <QTime>
#include <qbuffer.h>

SplashWidget::SplashWidget():
    m_label(new QLabel(this)),
    m_movie(new QMovie(this)),
    m_sm(new QSharedMemory("splash_sm")),
    m_elapseMs(-1),
    m_elapseTimerId(-1),
    m_shareMemoryReadId(-1),
    m_file(new QFile(this))
{
    setWindowFlags(Qt::FramelessWindowHint| Qt::WindowSystemMenuHint);
    setAttribute(Qt::WA_DeleteOnClose);
    resize(1920,1080);

    //加载动画
    QString strGif = QApplication::applicationDirPath() + "/laoding2.gif";

    m_movie->setFileName(strGif);

    m_label->setWindowFlags(Qt::FramelessWindowHint| Qt::WindowSystemMenuHint);
    m_label->setMovie(m_movie);
    m_label->setScaledContents(true);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(m_label);
    setLayout(layout);

    //记录
    QString logPath = QApplication::applicationDirPath() +
            "/splashlog.txt";
    m_file->setFileName(logPath);
    if(false == m_file->open(QIODevice::WriteOnly)){
        qDebug()<<"open failed.";
    }

    m_textStream.setDevice(m_file);
}

SplashWidget::~SplashWidget()
{
    QString currentTimeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd:hh:mm:ss.zzz");
    writeLog(QString("close|").append(currentTimeStr));

    m_movie->deleteLater();
    m_label->deleteLater();
    m_sm->deleteLater();

    m_file->close();
    m_file->deleteLater();
}

void SplashWidget::setElapsedMs(const int ms)
{
    m_elapseTimerId = startTimer(ms);
}

void SplashWidget::setShareMemoryReadMs(const int ms)
{
    //ms == 0,关闭共享内存
    if(ms == 0){
        return;
    }else{
        //创建共享内存
        if(true == m_sm->isAttached()){
            m_sm->detach();
        }
        //设置空间
        if(false == m_sm->create(100)){
            qDebug()<<"create failed."<<m_sm->errorString();
            return;
        }

        m_shareMemoryReadId = startTimer(ms);
    }
}

void SplashWidget::writeLog(const QString s)
{
    m_textStream<<s<<endl;
//    m_textStream<<s<<"\r\n";
}

void SplashWidget::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == m_elapseTimerId){
        writeLog("Timeout,splash exit.");
        qDebug()<<"timerevent";
        qDebug()<<geometry();

        close();
        emit sigQuit();
    }else if(event->timerId() == m_shareMemoryReadId){
        //加锁
        if(false == m_sm->lock()){
            writeLog(QString("lock failed,").append(
                         m_sm->errorString()));
            return;
        }

        QBuffer buf;
        buf.open(QIODevice::WriteOnly);
        buf.write((char*)m_sm->data());
        buf.close();

        //解锁
        if(false == m_sm->unlock()){
//            qDebug()<<"unlock failed."<<m_sm->errorString();
            writeLog(QString("unlock failed,").append(
                         m_sm->errorString()));
            return;
        }
        //一旦接收到数据，延时一秒退出
        if(buf.data().size() != 0){
            writeLog("Get shareMemory data,splash exit.");
            m_sm->detach();

            emit sigQuit();
        }
    }
}

void SplashWidget::showEvent(QShowEvent *)
{
    m_movie->start();
}
