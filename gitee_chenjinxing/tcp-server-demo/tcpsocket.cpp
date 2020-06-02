#include <QDebug>

#include "tcpsocket.h"
#include "receiverservice.h"

TcpSocket::TcpSocket(QObject *parent) :
    QTcpSocket(parent)
{
    _blockSize =0;
    _cmdType =0;
    //关联接收数据的信号和槽
    connect(this,SIGNAL(readyRead()),this,SLOT(receiveMessage()));
}


void TcpSocket::receiveMessage()
{
    QDataStream in(this);   //定义接收数据的流，构造的时候绑定socket
    in.setVersion(QDataStream::Qt_5_6);

    //从in中解析数据
    //先去接收包头
    if(_blockSize ==0)
    {
        //如果还没接收完包头，就直接返回
        if(this->bytesAvailable() <sizeof(_blockSize))
            return;
        //接收完包头，就把包头的值保存下来
        in >>_blockSize;
    }
    //再去接收类型
    if(_cmdType ==0)
    {
        //如果还没接收完类型，就直接返回
        if(this->bytesAvailable() <sizeof(_cmdType))
            return;
        //接收完类型，就把类型的值保存下来
        in >>_cmdType;
    }
    //根据包体大小判断是否接收完了数据
    int initBytes =this->bytesAvailable();
    if(initBytes <_blockSize)
        return;
    //根据类型获取处理器
    Receiver * pReceiver =ReceiverService::Instance()->getReceiver(_cmdType);
    if(pReceiver==nullptr)
        //错误处理
        qDebug()<<"找不到处理器";
        ;
    //处理请求
    pReceiver->parseData(this,in,_blockSize);

    //有可能一次发送多个消息
    _blockSize =0;
    _cmdType =0;
    if(bytesAvailable() >0)
    {
        this->receiveMessage(); //递归
    }
}

void TcpSocket::sendMessage(const QByteArray &data)
{
    //发送消息
    this->write(data);
}
