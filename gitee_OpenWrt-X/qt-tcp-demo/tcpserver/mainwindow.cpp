#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QTimer>
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

void MainWindow::init()
{
    timer = new QTimer;
    this->tcpServer = new QTcpServer(this);
    this->tcpSocket = new QTcpSocket(this);
    newListen();
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

}

void MainWindow::on_send_clicked()
{
    this->tcpSocket->write(ui->lineEdit->text().toLatin1());
}

void MainWindow::newListen()
{
    if(!tcpServer->listen(QHostAddress::Any,10000)){
        qDebug()<<tcpServer->errorString();
        close();
        return;
    }
}

void MainWindow::acceptConnection()
{
    tcpSocket = tcpServer->nextPendingConnection();
}

void MainWindow::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();
    tcpSocket->close();
}
