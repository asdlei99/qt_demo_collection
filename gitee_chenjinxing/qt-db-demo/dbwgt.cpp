#include <QHeaderView>
#include <QIntValidator>
#include <QMessageBox>
#include <QModelIndex>
#include "dbwgt.h"
#include "ui_dbwgt.h"

#include "userservice.h"
DbWgt::DbWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DbWgt)
{
    ui->setupUi(this);
    //设置userId只能为数字
    this->ui->userId->setValidator(new QIntValidator(0,9,this->ui->userId));
    QStringList header;
    header<<"用户ID"<<"用户名"<<"用户邮箱"<<"操作";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setColumnCount(header.length());
    //设置表格自适应宽度
    for(int i=0;i<ui->tableWidget->columnCount();i++){
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }
    this->flashAllUser();
}

DbWgt::~DbWgt()
{
    delete ui;
}


//新增
void DbWgt::on_addBtn_clicked()
{
    User newUser;
    newUser.setName(this->ui->userName->text());
    newUser.setEmail(this->ui->userEmail->text());
    if(UserService::Instance()->InsertUser(newUser)<1){
        QMessageBox::information(this,"错误","新增失败");
        return;
    }
    this->flashAllUser();
}
//修改
void DbWgt::on_modifyBtn_clicked()
{
    if(this->ui->userId->text().isEmpty()){
        QMessageBox::information(this,"错误","用户ID不能为空");
        return;
    }
    User newUser;
    newUser.setId(this->ui->userId->text().toInt());
    newUser.setName(this->ui->userName->text());
    newUser.setEmail(this->ui->userEmail->text());
    if(!UserService::Instance()->modifyUser(newUser)){
        QMessageBox::information(this,"错误","更新失败");
        return;
    }
    QMessageBox::information(this,"执行结果","更新成功");
    this->flashAllUser();
}
//刷新界面所有数据
void DbWgt::flashAllUser()
{
    //获取所有用户
    QList<User> users =UserService::Instance()->getAllUsers();
    ui->tableWidget->setRowCount(users.size());

    for(int i =0;i <users.size();i++){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(users.at(i).getId())));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(users.at(i).getName()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(users.at(i).getEmail()));

        QPushButton *button =new QPushButton("删除");
        connect(button,SIGNAL(clicked(bool)),this,SLOT(deleteOneUser()));
        ui->tableWidget->setCellWidget(i,3,button);
    }
}
//根据id删除用户
void DbWgt::deleteOneUser()
{
    QPushButton *button = dynamic_cast<QPushButton *>(QObject::sender()); //找到信号发送者
    QModelIndex index = ui->tableWidget->indexAt(button->pos());   //定位按钮
    QTableWidgetItem *item = ui->tableWidget->item(index.row(), 0);//得到item
    int userId =item->text().toInt();
    if(!UserService::Instance()->deleteUser(userId)){
        QMessageBox::information(this,"错误","删除失败");
        return;
    }
    QMessageBox::information(this,"执行结果","删除成功");
    this->flashAllUser();
}
