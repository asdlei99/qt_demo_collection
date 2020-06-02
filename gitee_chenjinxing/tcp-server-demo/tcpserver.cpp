#include <QTimer>
#include <QDebug>

#include "tcpserver.h"
#include "tcpsocket.h"
#include "servermanager.h"


TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{

}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"新的连接请求,连接描述符:"<<socketDescriptor;
    //创建socket
    TcpSocket *tcpSocket=new TcpSocket(this);

    //设置socket描述符
    tcpSocket->setSocketDescriptor(socketDescriptor);

    //创建好了和客户端进行通讯的socket，需要添加到List进行管理
    ServerManager *serverManager =ServerManager::Instance();
    serverManager->addClient(tcpSocket);

}

