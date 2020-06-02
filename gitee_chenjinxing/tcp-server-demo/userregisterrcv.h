#ifndef USERREGISTERRCV_H
#define USERREGISTERRCV_H

#include "receiver.h"

class UserRegisterRcv : public Receiver
{
public:
    UserRegisterRcv();

    //用来解析数据 负责和客户端通讯的是socket，数据流是stream
    virtual void parseData(TcpSocket *socket, QDataStream &stream,const int &packSize);
};

#endif // USERREGISTERRCV_H
