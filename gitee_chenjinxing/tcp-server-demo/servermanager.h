#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H
#include "tcpsocket.h"
#include "tcpserver.h"
class ServerManager
{
private:
    ServerManager();
public:
    static ServerManager *Instance(){
        static ServerManager T;
        return &T;
    }
private:
    TcpServer * _tcpServer;
    QList<TcpSocket*> _tcpSocketList;
public:
    //启动服务器：
    bool start(int port);
    //停止服务器
    void stop(void);

    //添加已连接的socket到list中
    void addClient(TcpSocket *tcpSocket);
    //删除一个socket 断网时使用
    void deleteClient(int num);
};

#endif // SERVERMANAGER_H
