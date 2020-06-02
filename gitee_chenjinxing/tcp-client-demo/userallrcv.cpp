#include <QDebug>
#include "userallrcv.h"
#include "user.h"
#include "public.h"
#include "clientmanager.h"
UserAllRcv::UserAllRcv()
{

}

void UserAllRcv::sendData()
{
    QByteArray data;    //用来暂时存放发送的数据
    QDataStream out(&data,QIODevice::WriteOnly);    //给暂存数据绑定流
    out.setVersion(QDataStream::Qt_5_6);//设置版本信息
    //数据整合开始
    out <<(quint16)0;   //预留两个字节的空间，类型转化非常重要
    out <<(quint16)DATA_TYPE::USER_ALL; //把消息类型写进包体

    //不需要写包体

    //把包体大小写包头
    out.device()->seek(0);//定位到包头位置
    out << (quint16)(data.size() -sizeof(quint16) -sizeof(quint16));
    //发送消息
    if(!ClientManager::Instance()->getTcpSocket()->sendMessage(data)){
        qDebug()<<"写入错误";
        return;
    }
    ClientManager::Instance()->getTcpSocket()->waitForReadyRead();
}

void UserAllRcv::parseData(TcpSocket *socket, QDataStream &stream, const int &packSize)
{
    //先解析用户总数
    int userNum;
    stream >>userNum;
    for(int i=0;i <userNum;i++){
        int userId;
        QString name;
        QString email;
        stream >>userId;
        stream >>name;
        stream >>email;
        qDebug()<<"\t"<<"用户ID:"<<userId<<"\t"<<"用户名:"<<name<<"\t"<<"用户邮箱:"<<email<<"\n";
    }
}

