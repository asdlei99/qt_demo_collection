#include "roomwgt.h"
#include "ui_roomwgt.h"
#include <QPalette>
#include <QPainter>

RoomWgt::RoomWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomWgt)
{
    ui->setupUi(this);

    //设置背景颜色
    //this->setStyleSheet("background-color:gray;border:1px solid red;");
    this->setStyleSheet("background-color:#EEEEEE;");

//    QPalette pal(this->palette());
//    pal.setColor(QPalette::Background,Qt::red);
//    this->setAutoFillBackground(true);
//    this->setPalette(pal);
}

RoomWgt::~RoomWgt()
{
    delete ui;
}

void RoomWgt::initRoom(const QString &user1, const QString &user2, const QString &user3, bool isBeginGame)
{
    //三个头像控件
    this->ui->userHead1->setUserName(user1);
    this->ui->userHead2->setUserName(user2);
    this->ui->userHead3->setUserName(user3);
    //一个桌子控件
    this->ui->roomWgt->setIsBeginGame(isBeginGame);
}
void RoomWgt::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}
