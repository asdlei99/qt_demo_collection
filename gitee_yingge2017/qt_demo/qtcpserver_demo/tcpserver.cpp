#include "tcpserver.h"

#include <QTcpServer>
#include <qdebug.h>
#include <QThread>
#include <qdatetime.h>

const int ConPort = 2222;

TcpServer::TcpServer(QObject *parent) : QObject(parent)
  , m_pServer(new QTcpServer)
{
    connect(m_pServer,&QTcpServer::newConnection,
            this,&TcpServer::slotNewConnection);
    if(true == m_pServer->listen(QHostAddress::Any,ConPort)){
        qDebug()<<"listen succ";
    }else{
        qDebug()<<"listen failed."
               <<m_pServer->errorString();
    }
}

void TcpServer::slotNewConnection()
{
    // QTcpSocket *QTcpServer::nextPendingConnection()
    m_pClientSocket = m_pServer->nextPendingConnection();
    connect(m_pClientSocket, &QTcpSocket::readyRead,
            this, &TcpServer::slotRead);
    connect(m_pClientSocket, &QTcpSocket::disconnected,
            this, &TcpServer::slotDisconnected);
#if 0
    connect(m_pClientSocket, QTcpSocket::error,
            this, &TcpServer::slotError);
#endif

    QString strClientAddress = m_pClientSocket->peerAddress().toString();
    int clientPort = m_pClientSocket->peerPort();
    qDebug()<<"new client connected,client address:"
           <<strClientAddress
          <<",client port:"<<clientPort;

    //	slotRead();
//    sendData();

}
void TcpServer::slotRead() {
    qDebug() << "slotRead";
    qDebug()<<m_pClientSocket->readAll();

    //    QString dataStr = QString::fromRawData(m_pClientSocket->readAll().data());
    //    qDebug() << "slotRead:" << dataStr;

#if 0
    while (true) {
        if (m_pClientSocket->bytesAvailable() > 0) {
            QByteArray ba = m_pClientSocket->readAll();
            qDebug() << "slotRead:" << ba;
            QThread::msleep(100);
        }
        else {
            qDebug() << "client socket bytesAvailable false";
            qDebug()<<m_pClientSocket->errorString();
            return;
        }
    }
#endif
}

void TcpServer::slotDisconnected() {
    qDebug() << "client disconnected";
}
void TcpServer::slotError(QAbstractSocket::SocketError socketError) {
    qDebug() << "error:" << m_pClientSocket->errorString();
}

void TcpServer::sendData()
{
    while(true){
//        QString str = QDateTime::currentDateTime().toString(Qt::ISODateWithMs);
      //  int re = m_pSocket->write(str.toLocal8Bit().data(),str.size());
        QString str = "server data----";
          int re = m_pClientSocket->write(str.toStdString().data());
        if(re < 0){
            qDebug()<<"socket write failed";
        }else{
            qDebug()<<"socket write succ,re:"<<re<<"|data:"<<str;
        }
        QThread::msleep(1000);
    }
}

