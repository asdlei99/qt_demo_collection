#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpSocket>
#include <qdebug.h>
#include <qdatetime.h>
#include <qthread.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

TcpClient::TcpClient()
    : m_pSocket(new QTcpSocket(this))
    , m_bStop(false)
{
    connect(m_pSocket,&QTcpSocket::disconnected,
            this,&TcpClient::slotDisconnected);
    //socket连接成功将触发槽函数
    connect(m_pSocket,&QTcpSocket::connected,
            this,&TcpClient::slotCennected);
    m_pSocket->connectToHost("127.0.0.1",2222);
    //阻塞等待连接成功
    if(true == m_pSocket->waitForConnected(3000)){
        qDebug()<<"socket connected succ";
    }else{
        qDebug()<<"socket connect to host failed.";
    }
}

void TcpClient::slotCennected()
{
    while(true){
        if(m_bStop){
            return;
        }
        QString str = QDateTime::currentDateTime().toString(Qt::ISODateWithMs);
        //  int re = m_pSocket->write(str.toLocal8Bit().data(),str.size());
        //          int re = m_pSocket->write(str.toStdString().data());
        int re = m_pSocket->write(str.toUtf8());
        m_pSocket->flush();
        if(re < 0){
            qDebug()<<"socket write failed";
        }else{
            qDebug()<<"socket write succ,re:"<<re<<"|data:"<<str;
        }
        QThread::msleep(1000);
    }
}

void TcpClient::slotDisconnected()
{
    m_bStop = true;
    qDebug()<<"TcpClient::slotDisconnected";
}
