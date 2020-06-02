#ifndef RECEIVERSERVICE_H
#define RECEIVERSERVICE_H
#include <QMap>

#include "public.h"
#include "receiver.h"
class ReceiverService
{
private:
    ReceiverService();
public:
    //获取所有的解析类
    QMap<quint16, Receiver *> getReceivers() const;
    Receiver *getReceiver(quint16 receiveType);
    //单例模式
    static ReceiverService* Instance(){
        static ReceiverService T;
        return &T;
    }

private:
    QMap<quint16,Receiver*> receivers;
};

#endif // RECEIVERSERVICE_H
