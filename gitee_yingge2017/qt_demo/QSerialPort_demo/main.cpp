#include <QCoreApplication>
#include <qdebug.h>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "serialport.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        qDebug() << "Serial Number: " << info.serialNumber();
        qDebug() << "System Location: " << info.systemLocation();
        qDebug()<<"portName"<< info.portName();
        qDebug() <<QString("pid:0x%1").arg(info.productIdentifier(),4,16,QLatin1Char('0'));
        qDebug() <<QString("vid:0x%1").arg(info.vendorIdentifier(),4,16,QLatin1Char('0'));
        qDebug()<<"";
    }

    SerialPort s;

    //    if(sp->isOpen()){
    //        sp->clear();
    //        sp->close();
    //    }
    //    delete sp;
    //    sp=nullptr;

    return a.exec();
}
