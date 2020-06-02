#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qdatetime.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _udpSocket(new QUdpSocket(this))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_broadcast_clicked()
{
    QString s = QDateTime::currentDateTime().toString(Qt::ISODateWithMs);
    int re = _udpSocket->writeDatagram(
                s.toLocal8Bit(),
                QHostAddress::Broadcast,
                9999);
    if(re > 0){
        qDebug()<<"send broad cast :"<<re<<" "<<s;
    }else{
        qDebug()<<"send broad cast failed.";
    }
}
