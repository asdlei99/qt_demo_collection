#include "findfriend.h"
#include "ui_findfriend.h"

#include "qfiletrans.h"
#include "loginwindow.h"
#include "listwindow.h"
#include <QDebug>

//���Һ���
FindFriend::FindFriend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindFriend)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
        flags |=Qt::WindowMinimizeButtonHint ;
        setWindowFlags(flags);
    this->setWindowTitle(LOCAL("��Ӻ���"));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(addFriend()));
}
//��Ӻ���
void FindFriend::addFriend()
{
    QString tojid = ui->lineEdit->text();

    QString str = "<presence from=\"\" to=\"";
       str += tojid;
      str += "\" type=\"subscribe\"> </presence>";
    Loginwindow::getclient()->sendData(str.toLocal8Bit());
    this->close();
}
FindFriend::~FindFriend()
{
    delete ui;
}
