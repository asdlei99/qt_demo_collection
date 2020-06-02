#include "clientmanager.h"

ClientManager::ClientManager()
{
    this->tcpSocket =new TcpSocket();
}

TcpSocket *ClientManager::getTcpSocket() const
{
    return tcpSocket;
}

void ClientManager::startConnect(const QString &ip, const QString &port)
{
    tcpSocket->setServerIp(ip);
    tcpSocket->setServerPort(port);

    tcpSocket->connectToServer();

    tcpSocket->waitForConnected();
}
