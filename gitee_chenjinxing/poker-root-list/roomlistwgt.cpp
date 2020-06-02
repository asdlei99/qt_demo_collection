#include "roomlistwgt.h"
#include "ui_roomlistwgt.h"

#include <QLabel>
#include <QPixmap>
#include <QGridLayout>
#include <QPushButton>

#include "qpixmaphelper.h"
#include "roomwgt.h"

RoomListWgt::RoomListWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomListWgt)
{
    ui->setupUi(this);
    this->ui->listWidget->setViewMode(QListView::IconMode); //图标模式
    this->ui->listWidget->setResizeMode(QListView::Adjust);
    this->ui->listWidget->setSpacing(4);
}

RoomListWgt::~RoomListWgt()
{
    delete ui;
}

void RoomListWgt::on_addRoom_clicked()
{
    //新增添加项
    QListWidgetItem * newItem =new QListWidgetItem();
    newItem->setSizeHint(QSize(210,220));
    this->ui->listWidget->addItem(newItem);
    //新增RoomWgt
    RoomWgt * roomWgt =new RoomWgt(this);
    roomWgt->initRoom(this->ui->user1->text(),
                      this->ui->user2->text(),
                      this->ui->user3->text(),
                      this->ui->isBeginGame->isChecked());
    this->ui->listWidget->setItemWidget(newItem,roomWgt);
}

