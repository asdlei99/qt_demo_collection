#include "DialogCheck.h"
#include "ui_DialogCheck.h"
#include <QStandardItem>
#include "CheckBoxDelegate.h"

DialogCheck::DialogCheck(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCheck)
{
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel(5, 5, this);

    for(int i = 0;i<4;i++){
        model->setData(model->index(1,i+1), QString("1"), Qt::EditRole);
    }
    CheckBoxDelegate *ck = new CheckBoxDelegate();

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(ck);

    // set check
    QModelIndex index = model->index(0,0, QModelIndex());
    model->setData(index, true, Qt::EditRole);
    // 设置编辑状态
//    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//    ui->tableView->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

DialogCheck::~DialogCheck()
{
    delete ui;
}
