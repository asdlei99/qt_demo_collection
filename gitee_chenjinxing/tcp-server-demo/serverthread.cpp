#include <QDebug>

#include "serverthread.h"
#include "servermanager.h"

ServerThread::ServerThread()
{

}

void ServerThread::run()
{
    //开启服务
    if(ServerManager::Instance()->start(8089)){
        qDebug()<<"启动成功";
    }else{
        qDebug()<<"启动失败";
    }
}

void ServerThread::startServer()
{
    this->start();
}
