#include "receiverservice.h"
#include "userregisterrcv.h"
#include "userallrcv.h"
ReceiverService::ReceiverService()
{
    //初始化所有的解析方法
    receivers[(quint16)DATA_TYPE::USER_REGISTER] =new UserRegisterRcv();
    //receivers[(quint16)DATA_TYPE::USER_LOGIN] =new UserLoginRcv();
    receivers[(quint16)DATA_TYPE::USER_ALL] =new UserAllRcv();
}

QMap<quint16, Receiver *> ReceiverService::getReceivers() const
{
    return receivers;
}

Receiver *ReceiverService::getReceiver(quint16 receiveType)
{
    if(this->receivers.find(receiveType)!=this->receivers.end())
        return this->receivers.find(receiveType).value();
    return nullptr;
}

