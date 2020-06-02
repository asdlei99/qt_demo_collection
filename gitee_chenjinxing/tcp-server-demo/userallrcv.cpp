#include <QDebug>
#include "userallrcv.h"
#include "userservice.h"
#include "user.h"
#include "public.h"
UserAllRcv::UserAllRcv()
{

}

void UserAllRcv::parseData(TcpSocket *socket, QDataStream &stream, const int &packSize)
{
    //获取所有的用户 不需要传递参数 也就不用解析数据 直接返回数据
    //获取所有用户
    QList<User> users =UserService::Instance()->getAllUsers();
    //返回给客户端数据 先返回用户总数，再逐条返回user数据
    QByteArray data;    //用来暂时存放发送的数据
    QDataStream out(&data,QIODevice::WriteOnly);    //给暂存数据绑定流
    out.setVersion(QDataStream::Qt_5_6);//设置版本信息
    //数据整合开始
    out <<(quint16)0;   //预留两个字节的空间，类型转化非常重要
    out <<(quint16)DATA_TYPE::USER_ALL; //把消息类型写进包体

    out <<users.size(); //返回用户总数
    //逐条返回用户数据
    for(User &user:users){
        out <<user.getId();
        out <<user.getName();
        out <<user.getEmail();
    }
    //把包体大小写包头
    out.device()->seek(0);//定位到包头位置
    out << (quint16)(data.size() -sizeof(quint16) -sizeof(quint16));
    //发送消息
    socket->write(data);
    socket->waitForBytesWritten();

}
