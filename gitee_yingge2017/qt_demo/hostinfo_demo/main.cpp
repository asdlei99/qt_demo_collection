#include <QCoreApplication>
#include <qsysinfo.h>
#include <qdebug.h>
#include <QHostInfo> //QT += network
#include <QNetworkInterface>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug()<<QHostInfo::localHostName();
    qDebug()<<QHostInfo::localDomainName();
    //    qDebug()<<getCpu();
    QHostInfo hi;
    qDebug()<<hi.addresses().size();

    QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
    qDebug()<<info.addresses();

    QList<QNetworkInterface> niList = QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface ni,niList){
        qDebug()<<"hardwareAddress:"<<ni.hardwareAddress();
        qDebug()<<"humanReadableName:"<<ni.humanReadableName();
        qDebug()<<"name:"<<ni.name();
        qDebug();
    }

    //Qt4 QSysInfo 类中的函数只能返回计算机信息的枚举类型
    //    Qt5 QSysInfo 增加了多个静态函数，可以获取计算机信息
    qDebug()<<"QSysInfo------------------------------------";
    qDebug()<<QSysInfo::buildAbi();
    qDebug()<<QSysInfo::buildCpuArchitecture();
    qDebug()<<QSysInfo::currentCpuArchitecture();
    qDebug()<<QSysInfo::kernelType();
    qDebug()<<QSysInfo::kernelVersion();
    qDebug()<<QSysInfo::machineHostName();
    qDebug()<<QSysInfo::machineUniqueId();
    qDebug()<<QSysInfo::prettyProductName();
    qDebug()<<QSysInfo::productType();
    qDebug()<<QSysInfo::productVersion();


    return a.exec();
}
