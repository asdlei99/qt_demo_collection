#ifndef USERALLRCV_H
#define USERALLRCV_H

#include "receiver.h"
class UserAllRcv :public Receiver
{
public:
    UserAllRcv();

    virtual void parseData(TcpSocket* socket,QDataStream &stream,const int &packSize);

    virtual void sendData();
};

#endif // USERALLRCV_H
