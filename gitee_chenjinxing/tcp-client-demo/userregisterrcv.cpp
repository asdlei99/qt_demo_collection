#include "userregisterrcv.h"

#include "public.h"
#include "clientmanager.h"
#include <QDebug>
User UserRegisterRcv::getAddUser() const
{
    return addUser;
}

void UserRegisterRcv::setAddUser(const User &value)
{
    addUser = value;
}

UserRegisterRcv::UserRegisterRcv()
{

}

void UserRegisterRcv::parseData(TcpSocket *socket, QDataStream &stream, const int &packSize)
{

    int userId;
    QString name;
    QString email;
    stream >>userId;
    stream >>name;
    stream >>email;
    if(userId ==-1){
        qDebug() <<"新增user失败";
        return;
    }
    qDebug()<<"新增用户成功,"<<"用户ID:"<<userId<<"用户名"<<name<<"用户邮箱"<<email;
}

void UserRegisterRcv::sendData()
{
    //新增成功 直接返回新增后的user
    QByteArray data;    //用来暂时存放发送的数据
    QDataStream out(&data,QIODevice::WriteOnly);    //给暂存数据绑定流
    out.setVersion(QDataStream::Qt_5_6);//设置版本信息
    //数据整合开始
    out <<(quint16)0;   //预留两个字节的空间，类型转化非常重要
    out <<(quint16)DATA_TYPE::USER_REGISTER; //把消息类型写进包体
    out <<this->addUser.getName();
    out <<this->addUser.getEmail();

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
