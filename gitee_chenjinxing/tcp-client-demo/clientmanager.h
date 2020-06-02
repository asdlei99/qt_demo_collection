#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H
#include "tcpsocket.h"

class ClientManager
{
private:
    ClientManager();
public:
    static ClientManager *Instance(){
        static ClientManager T;
        return &T;
    }
private:
    TcpSocket * tcpSocket;
public:
    void startConnect(const QString& ip, const QString &port);
    TcpSocket *getTcpSocket() const;
};

#endif // CLIENTMANAGER_H
