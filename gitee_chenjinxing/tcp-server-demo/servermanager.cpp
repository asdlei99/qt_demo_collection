#include "servermanager.h"
ServerManager::ServerManager()
{
    _tcpServer =new TcpServer();
}

bool ServerManager::start(int port)
{
    //启动监听
    return _tcpServer->listen(QHostAddress::Any,port);
}

void ServerManager::stop()
{
    //关闭tcpServer
    _tcpServer->close();
}

void ServerManager::addClient(TcpSocket *tcpSocket)
{
    _tcpSocketList.append(tcpSocket);
}

void ServerManager::deleteClient(int num)
{
    TcpSocket* theSocket =_tcpSocketList.at(num);
    _tcpSocketList.removeAt(num);
    theSocket->close();
    delete(theSocket);
}
