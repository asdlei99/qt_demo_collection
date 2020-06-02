#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qdebug.h>

const int ConPort = 9999;
const QString ConIp = "225.0.0.1";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _tcpServer(new QTcpServer(this)),
    _udpSocket(new QUdpSocket(this))
{
    ui->setupUi(this);
#if 0
    if(_tcpServer->listen(QHostAddress::Any,ConPort)){
        qDebug()<<"listen succ";
    }else{
        qDebug()<<"listen failed";
        return ;
    }
    connect(_tcpServer,&QTcpServer::newConnection,
            this,&MainWindow::newConnect);
#endif

#if 0
    if(_udpSocket->bind(ConPort,
                        QAbstractSocket::ShareAddress)){
        qDebug()<<"udp bind succ";
    }else{
        qDebug()<<"udp bind failed";
    }
    connect(_udpSocket,&QUdpSocket::readyRead,
            this,&MainWindow::slotUdpReadyRead);
#endif

    if(_udpSocket->bind(QHostAddress::AnyIPv4,
                        ConPort,
                        QUdpSocket::ShareAddress)){
        qDebug()<<"udp bind succ";
    }else{
        qDebug()<<"udp bind failed";
    }
    if(_udpSocket->joinMulticastGroup(QHostAddress(ConIp))){
        qDebug()<<"join succ";
    }else{
        qDebug()<<"join failed";
    }

    connect(_udpSocket,&QUdpSocket::readyRead,
            this,&MainWindow::slotUdpReadyRead);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnect()
{
    _clientTcpSocket = _tcpServer->nextPendingConnection();
    qDebug()<<"new Connect--"<<_clientTcpSocket->peerAddress();

    connect(_clientTcpSocket,&QTcpSocket::readyRead,
            this,&MainWindow::readyRead);
}

void MainWindow::readyRead()
{
    qDebug()<<_clientTcpSocket->readAll();
}

void MainWindow::slotUdpReadyRead()
{
    qDebug()<<"slot updp ready read";
    QByteArray datagram;
    datagram.resize(_udpSocket->pendingDatagramSize());
    _udpSocket->readDatagram(datagram.data(),datagram.size());
    qDebug()<<datagram;
}
