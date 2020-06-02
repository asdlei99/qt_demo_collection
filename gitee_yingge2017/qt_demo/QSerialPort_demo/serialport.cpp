#include "serialport.h"

#include <qdebug.h>
#include <qdatetime.h>

const QString conSPName = "COM3";

SerialPort::SerialPort(QObject*parent)
    :QObject(parent)
{
    //1.初始化
    m_sp = new QSerialPort();
    //    m_sp->setPortName("COM4");
    m_sp->setPortName(conSPName);
    //2.打开串口
    if(false == m_sp->open(QIODevice::ReadWrite)){
        qDebug()<<"open failed."
               <<m_sp->error();
    }
    else{
        qDebug()<<"open succ.";
    }
    //3.设置
    //设置波特率和读写方向
    m_sp->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);
    m_sp->setDataBits(QSerialPort::Data8);      //数据位为8位
    m_sp->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    m_sp->setParity(QSerialPort::NoParity); //无校验位
    m_sp->setStopBits(QSerialPort::OneStop); //一位停止位

    //4.连接信号槽
    connect(m_sp,&QSerialPort::readyRead,
            this,&SerialPort::slotReadData);
    //写数据定时器
    //    startTimer(500);
}

SerialPort::~SerialPort()
{
    if(m_sp->isOpen()){
        m_sp->clear();
        m_sp->close();
    }
    delete m_sp;
    m_sp=nullptr;
}

void SerialPort::timerEvent(QTimerEvent *event)
{
    QString str = QDateTime::currentDateTime().toString(Qt::ISODate);
    int num = m_sp->write(str.toStdString().data(),str.length());
    if(num == -1){
        qDebug()<<"timerEvent write failed.";
    }else{
        qDebug()<<"timeEvent write ok|num:"<<num;
    }
}

void SerialPort::slotReadData()
{
    QByteArray info = m_sp->readAll();

    qDebug()<<"receive info:"<<info;
}
