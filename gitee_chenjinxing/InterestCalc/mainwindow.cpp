#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
#include <QDebug>
#include <QMessageBox>
#include <QAction>
#include "xexcel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowTitle("还款利息计算器");

    ui->setupUi(this);
    ui->lineEdit->setText(QString::number(3.89));
    ui->lineEdit_2->setText("160000.000");
    ui->edit_month->setText("36");


    ui->comboBox->setEditable(false);
    ui->comboBox->insertItem(1,"等额本息法");
    ui->comboBox->insertItem(2,"等额本金法");
    ui->comboBox->insertItem(3,"等本等息法");

    initTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTable()
{
    //设置表头
    QStringList head;
    head.push_back("期号");
    head.push_back("月供");
    head.push_back("月供金额");
    head.push_back("月供利息");
    head.push_back("本金余额");

    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customContextMenuRequested(QPoint)));

    ui->tableWidget->setColumnCount(head.size());//设置表头大小
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);  //设置为可以选中多个目标
    ui->tableWidget->setHorizontalHeaderLabels(head);
    for(int i =0;i <head.size();i++)
    {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    double benjin =ui->lineEdit_2->text().toDouble();
    double nianLilv =ui->lineEdit->text().toDouble();
    double leijililv =0.00;
    if(ui->comboBox->currentText().contains("等额本息"))
        leijililv =debxToTable( benjin,  nianLilv);
    else if(ui->comboBox->currentText().contains("等额本金"))
        leijililv =debjToTable( benjin,  nianLilv);
    else if(ui->comboBox->currentText().contains("等本等息"))
        leijililv =dbdxToTable( benjin,  nianLilv);

    ui->lineEdit_3->setText(QString::number(leijililv*100));
}
void MainWindow::on_pushButton_2_clicked()
{
    double benjin =ui->lineEdit_2->text().toDouble();
    double leiji =ui->lineEdit_3->text().toDouble();
    leiji =leiji/100;
    for(double i=0.000;i <20.000;i=i+0.001)
    {
        double leijililv =zhengtui(benjin,i);
        if(leijililv >leiji)
        {
            ui->lineEdit->setText(QString::number(i));
            return;
        }
    }
    QMessageBox::information(0,"ero","asdfasdf",QMessageBox::Cancel);
}

double MainWindow::zhengtui(double benjin, double nianLilv)
{
    nianLilv =nianLilv/100;
    double yueLilv  =nianLilv/12;
    int month =ui->edit_month->text().toInt();

    double pow =qPow(1+yueLilv,month);
    double yuehuankuan =benjin*yueLilv*pow/(pow-1);

    QStringList shengyuedaikuan_s;
    QStringList lixi_s;
    double lixi =0.00;

    double a =benjin;
    double leijililv =0.0000;
    double sumlixi =0.0000;
    for(int i=0;i <month;i++)
    {
        lixi =a*yueLilv;
        qDebug()<<a<<lixi;
        sumlixi +=lixi;
        lixi_s.append(QString::number(lixi));
        shengyuedaikuan_s.append(QString::number(a));
        a=a*(1+yueLilv) -yuehuankuan;
    }
    leijililv =sumlixi/benjin;
    qDebug()<<leijililv;
    return leijililv;
}
//等额本息
double MainWindow::debxToTable(double benjin, double nianLilv)
{
    nianLilv =nianLilv/100;
    double yueLilv  =nianLilv/12;
    int month =ui->edit_month->text().toInt();

    double pow =qPow(1+yueLilv,month);
    double yuehuankuan =benjin*yueLilv*pow/(pow-1);

    double lixi =0.00;

    double a =benjin;
    double sumlixi =0.0000;
    for(int i=0;i <month;i++)
    {
        lixi =a*yueLilv;
        qDebug()<<a<<lixi;
        sumlixi +=lixi;
        a=a*(1+yueLilv) -yuehuankuan;

        if(i ==month -1)
            a =0;
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(i+1)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(yuehuankuan)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(QString::number(yuehuankuan-lixi)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(QString::number(lixi)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(QString::number(a)));
    }
    ui->edit_lixi_all->setText(QString::number(sumlixi));
    double leijililv =sumlixi/benjin;
    qDebug()<<leijililv;
    return leijililv;
}
//等额本金
double MainWindow::debjToTable(double benjin, double nianLilv)
{
    nianLilv =nianLilv/100;
    double yueLilv  =nianLilv/12;

    int month =ui->edit_month->text().toInt();
    double yuegongbenjin=benjin/month;
    double benjinyue=benjin;
    double yuegonglixi =0.000;
    double sumlixi =0.0000;
    for(int i =0;i <month;i++)
    {
        yuegonglixi =benjinyue *yueLilv;
        sumlixi +=yuegonglixi;

        benjinyue -=yuegongbenjin;

        if(i ==month -1)
            benjinyue =0;
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(i+1)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(yuegongbenjin +yuegonglixi)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(QString::number(yuegongbenjin)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(QString::number(yuegonglixi)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(QString::number(benjinyue)));
    }
    ui->edit_lixi_all->setText(QString::number(sumlixi));
    double leijililv =sumlixi/benjin;
    qDebug()<<leijililv;
    return leijililv;

}
//等本等息
double MainWindow::dbdxToTable(double benjin, double nianLilv)
{
    nianLilv =nianLilv/100;
    double yueLilv  =nianLilv/12;

    int month =ui->edit_month->text().toInt();
    double yuegongbenjin=benjin/month;
    double benjinyue=benjin;
    double yuegonglixi =0.000;
    double sumlixi =0.0000;
    for(int i =0;i <month;i++)
    {
        yuegonglixi =benjin *yueLilv; //每个月利息都等于 借款金额*月利率
        sumlixi +=yuegonglixi;

        benjinyue -=yuegongbenjin;

        if(i ==month -1)
            benjinyue =0;
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(i+1)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(yuegongbenjin +yuegonglixi)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(QString::number(yuegongbenjin)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(QString::number(yuegonglixi)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(QString::number(benjinyue)));
    }
    ui->edit_lixi_all->setText(QString::number(sumlixi));
    double leijililv =sumlixi/benjin;
    qDebug()<<leijililv;
    return leijililv;
}

void MainWindow::customContextMenuRequested(const QPoint &pos)
{
    QAction *save   =new QAction("save");
    QAction *clear =new QAction("clear");
    connect(save,SIGNAL(triggered(bool)),this,SLOT(saveListData(bool)));
    connect(clear,SIGNAL(triggered(bool)),this,SLOT(clearListData(bool)));
    QMenu * munu =new QMenu();
    munu->addAction(save);
    munu->addAction(clear);
    munu->exec(QCursor::pos());
}

void MainWindow::saveListData(bool a)
{
    QList<QStringList> lines;
    for(int i =0;i <ui->tableWidget->rowCount();i++)
    {
        QStringList line;
        for(int j =0;j <ui->tableWidget->columnCount();j++)
        {
            qDebug()<<ui->tableWidget->item(i,j)->text();
            line.append(ui->tableWidget->item(i,j)->text());
        }
        lines.append(line);
    }
    XExcel::Instance().saveList(lines);
}

void MainWindow::clearListData(bool a)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}
