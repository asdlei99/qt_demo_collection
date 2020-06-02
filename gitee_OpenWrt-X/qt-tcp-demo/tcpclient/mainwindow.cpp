#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::init()
{
    this->tcpSocket = new QTcpSocket(this);
    newTCPConnect();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(revData()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(display(QAbstractSocket::SocketError)));
}

void MainWindow::newTCPConnect()
{
    tcpSocket->abort();
    tcpSocket->connectToHost("127.0.0.1",10000);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::revData()
{
    QString datas = tcpSocket->readAll();
    ui->lineEdit->setText(datas);

}

void MainWindow::display(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();
    tcpSocket->close();
}
