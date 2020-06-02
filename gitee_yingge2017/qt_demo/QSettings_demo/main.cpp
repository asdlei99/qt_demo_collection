#include <QCoreApplication>
#include <QColor>
#include <qsettings.h>
#include <QDebug>

void write();
void read();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCoreApplication::setOrganizationName("MySoft");
    QCoreApplication::setOrganizationDomain("mysoft.com");
    QCoreApplication::setApplicationName("Star Runner");

    write();
    qDebug();
    read();

    return a.exec();
}

void write(){
    qDebug()<<"QSettings pro write.";

    //1
    //Qt中使用QSettings类读写ini文件
    //QSettings构造函数的第一个参数是ini文件的路径,第二个参数表示针对ini文件,第三个参数可以缺省
    QSettings *configIniWrite = new QSettings("qsettings_demo.ini", QSettings::IniFormat);
    //向ini文件中写入内容,setValue函数的两个参数是键值对
    //向ini文件的第一个节写入内容,ip节下的第一个参数
    configIniWrite->setValue("/ip/first", "192.168.0.1");
    //向ini文件的第一个节写入内容,ip节下的第二个参数
    configIniWrite->setValue("ip/second", "127.0.0.1");
    //向ini文件的第二个节写入内容,port节下的第一个参数
    configIniWrite->setValue("port/open", "2222");
    //2.保存颜色
    QColor c = QColor("red");
    configIniWrite->setValue("color",c);
    //写入完成后删除指针

    //3.beginGroup
    configIniWrite->beginGroup("mainwindow");
    configIniWrite->setValue("size", "1024*768");
    configIniWrite->setValue("fullScreen", "true");
    configIniWrite->endGroup();
    //4.beginWriteArray
    struct Login {
        QString userName;
        QString password;
    };
    QList<Login> logins;

    for(int i = 0; i<5;++i){
        Login l;
        l.userName = "name:" + QString::number(i);
        l.password = "pwd:" + QString::number(i);
        logins.push_back(l);
    }

    //     QSettings settings;
    configIniWrite->beginWriteArray("logins");
    for (int i = 0; i < logins.size(); ++i) {
        configIniWrite->setArrayIndex(i);
        configIniWrite->setValue("userName", logins.at(i).userName);
        configIniWrite->setValue("password", logins.at(i).password);
    }
    configIniWrite->endArray();

    delete configIniWrite;

    qDebug()<<"QSettings pro write end.";
}
void read(){
    qDebug()<<"QSettings pro read.";

    //1
    QSettings *configIniRead = new QSettings("qsettings_demo.ini", QSettings::IniFormat);
    //将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型
    QString ipResult = configIniRead->value("/ip/second").toString();
    QString portResult = configIniRead->value("/port/open").toString();
    //打印得到的结果
    qDebug() << ipResult;
    qDebug() << portResult;
    //2.读取颜色
    QColor color = configIniRead->value("color").value<QColor>();
    qDebug()<<"color:"<<color.name();
    //读入入完成后删除指针
    //3
    configIniRead->beginGroup("mainwindow");
    qDebug()<<"size:"<<configIniRead->value("size").toString();
    qDebug()<<"fullScreen:"<<configIniRead->value("fullScreen").toString();
    configIniRead->endGroup();
    //4
    struct Login {
        QString userName;
        QString password;
    };
    QList<Login> logins;

    int size = configIniRead->beginReadArray("logins");
    for(int i = 0; i < size; ++i){
        configIniRead->setArrayIndex(i);
        Login ln;
        ln.userName = configIniRead->value("userName").toString();
        ln.password = configIniRead->value("password").toString();
        logins.append(ln);
    }
    configIniRead->endArray();

    for(auto item:logins){
        qDebug()<<"userName:"<<item.userName;
        qDebug()<<"password:"<<item.password;
    }

    delete configIniRead;

    qDebug()<<"QSettings pro read end.";
}
