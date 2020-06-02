#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <iostream>
#include <string>
#include "clientmanager.h"
#include "userallrcv.h"
#include "userregisterrcv.h"
#include "clientmanager.h"

#include <iostream>


using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream qout(stdout);
    int action =-1;
    //菜单
    while(action !=0){
        qout <<QString("输入操作代码")<<endl;
        qout <<QString("1.连接服务器")<<endl;
        qout <<QString("2.新增用户")<<endl;
        qout <<QString("3.获取所有用户")<<endl;
        qout <<QString("0.退出")<<endl;
        cin >>action;
        if(action ==0)
            break;
        if(action ==1){
            qout <<QString("输入ip地址和端口号，以空格割开")<<endl;
            string ip;
            string port;
            cin >>ip >>port;
            ClientManager::Instance()->startConnect(QString::fromStdString(ip),QString::fromStdString(port));
        }else if(action ==2){
            qout <<QString("输入用户名和邮箱，以空格割开")<<endl;
            string name;
            string email;
            cin >>name >>email;
            User user;
            user.setEmail(QString::fromStdString(email));
            user.setName(QString::fromStdString(name));
            UserRegisterRcv urRcv;
            urRcv.setAddUser(user);
            urRcv.sendData();
        }else if(action ==3){
            UserAllRcv uaRcv;
            uaRcv.sendData();
        }
    }

    return a.exec();
}
