#include <QCoreApplication>
#include <QDebug>
#include "servermanager.h"
#include "serverthread.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //开启服务
    if(ServerManager::Instance()->start(8089)){
        qDebug()<<"启动成功";
    }else{
        qDebug()<<"启动失败";
    }
    return a.exec();
}
