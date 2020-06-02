#include "ModelViewDialog.h"
#include "ui_ModelViewDialog.h"
#include "model_view/StringListModel.h"

#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <QStandardItemModel>

ModelViewDialog::ModelViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModelViewDialog)
{
    ui->setupUi(this);

    // createListView();
    createStringListView();
}

ModelViewDialog::~ModelViewDialog()
{
    delete ui;
}

void ModelViewDialog::createListView()
{
    // 创建标准项模型
    QStandardItemModel* model = new QStandardItemModel;

    // 获取模型的根项（Root Item），根项是不可见的
    QStandardItem *parentItem = model->invisibleRootItem();

    // 创建标准项item0，并设置显示文本，图标和工具提示
    QStandardItem *item0 = new QStandardItem;
    item0->setText("A");
    QPixmap pixmap0(50, 50);
    pixmap0.fill("red");
    item0->setIcon(QIcon(pixmap0));
    item0->setToolTip("indexA");

    // 将创建的标准项作为根项的子项
    parentItem->appendRow(item0);

    // 将创建的标准项作为新的父项
    parentItem = item0;

    // 创建新的标准项，它将作为item0的子项
    QStandardItem *item1 = new QStandardItem;
    item1->setText("B");
    QPixmap pixmap1(50,50);
    pixmap1.fill("blue");
    item1->setIcon(QIcon(pixmap1));
    item1->setToolTip("indexB");
    parentItem->appendRow(item1);

    // 创建新的标准项，这里使用了另一种方法来设置文本、图标和工具提示
    QStandardItem *item2 = new QStandardItem;
    QPixmap pixmap2(50,50);
    pixmap2.fill("green");
    item2->setData("C", Qt::EditRole);
    item2->setData("indexC", Qt::ToolTipRole);
    item2->setData(QIcon(pixmap2), Qt::DecorationRole);
    parentItem->appendRow(item2);

    // 在树视图中显示模型
    QTreeView *view= new QTreeView();
    view->setModel(model);

    QGridLayout* layout = new QGridLayout();
//    layout->setColumnStretch(0, 1);
//    layout->setColumnStretch(1, 1);

    layout->addWidget(view, 0, 0);
//    layout->addWidget(new QPushButton("test"), 1, 1, 1, 1);
    setLayout(layout);

    // 获取item0的索引并输出item0的子项数目，然后输出了item1的显示文本和工具提示
    QModelIndex indexA = model->index(0, 0, QModelIndex());
    qDebug() << "indexA row count: " << model->rowCount(indexA);
    QModelIndex indexB = model->index(0, 0, indexA);
    qDebug() << "indexB text: " << model->data(indexB, Qt::EditRole).toString();
    qDebug() << "indexB toolTip: "
             << model->data(indexB, Qt::ToolTipRole).toString();
}

void ModelViewDialog::createStringListView()
{
    QStringList list;
    list << "a" << "b" << "c";
    StringListModel* model = new StringListModel(list);

    QListView *listView = new QListView;
    listView->setModel(model);

    QTableView *tableView = new QTableView;
    tableView->setModel(model);

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(listView, 0, 0);
    layout->addWidget(tableView, 0, 1);
    setLayout(layout);

    // insert and remove test
    model->insertRows(3, 2);
    model->removeRows(0, 1);
}
