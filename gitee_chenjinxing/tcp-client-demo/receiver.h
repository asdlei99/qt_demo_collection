#ifndef RECEIVER_H
#define RECEIVER_H

#include <QDataStream>
#include "tcpsocket.h"
class Receiver
{
public:
    Receiver();
    //用来解析数据 负责和客户端通讯的是socket，数据流是stream
    virtual void parseData(TcpSocket* socket,QDataStream &stream,const int &packSize)=0;
    virtual void sendData()=0;
};
#endif // RECEIVER_H
