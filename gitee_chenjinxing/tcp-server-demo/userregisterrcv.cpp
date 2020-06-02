#include "userregisterrcv.h"

#include "userservice.h"
#include "public.h"
UserRegisterRcv::UserRegisterRcv()
{

}

void UserRegisterRcv::parseData(TcpSocket *socket, QDataStream &stream, const int &packSize)
{
    QString name;
    QString email;
    stream >>name;
    stream >>email;
    User newUser;
    newUser.setName(name);
    newUser.setEmail(email);
    //新增失败
    if(UserService::Instance()->InsertUser(newUser)<1){
        newUser.setId(-1);
    }
    //新增成功 直接返回新增后的user
    QByteArray data;    //用来暂时存放发送的数据
    QDataStream out(&data,QIODevice::WriteOnly);    //给暂存数据绑定流
    out.setVersion(QDataStream::Qt_5_6);//设置版本信息
    //数据整合开始
    out <<(quint16)0;   //预留两个字节的空间，类型转化非常重要
    out <<(quint16)DATA_TYPE::USER_REGISTER; //把消息类型写进包体
    out <<newUser.getId();
    out <<newUser.getName();
    out <<newUser.getEmail();

    //把包体大小写包头
    out.device()->seek(0);//定位到包头位置
    out << (quint16)(data.size() -sizeof(quint16) -sizeof(quint16));
    //发送消息
    socket->write(data);
    socket->waitForBytesWritten();
}
