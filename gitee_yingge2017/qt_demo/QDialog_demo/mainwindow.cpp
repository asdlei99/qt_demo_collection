#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdialog.h>
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}


MainWindow::~MainWindow()
{
    d1->deleteLater();
    d2->deleteLater();
    d3->deleteLater();
    delete ui;
}

void MainWindow::on_pushButton_111_clicked()
{
    qDebug()<<"1111";

    d1 = new QDialog(this);
    d1->resize(222,222);
    d1->setWindowTitle("d1");
    d1->setAttribute(Qt::WA_DeleteOnClose);

    //模态运行，对话框打开之后不能在点击主窗口
    if(d1->exec() == QDialog::Accepted){
        return;
    }

    return;
}

void MainWindow::on_pushButton_22_clicked()
{
    /*
    1.当设置了model模式后，在调用show函数。等同于d1对话框调用exec的模式。
    鼠标不能再点击主窗口。
    2.当不设置model模式，调用show函数后。对话框和主窗口公用一个任务栏图标，
    但是鼠标仍然可以点击主窗口。
    */
    d2 = new QDialog(this);
    d2->resize(222,222);
    d2->setAttribute(Qt::WA_DeleteOnClose);
    d2->setWindowTitle("d2");
    //    d2->setModal(true);

    d2->show();
}

void MainWindow::on_pushButton33_clicked()
{
    /*
     * d3构造函数中不设置父窗口。子窗口产生新的任务栏图标。
     */
    d3 = new QDialog();
    d3->resize(222,222);
    d3->setAttribute(Qt::WA_DeleteOnClose);
    d3->setWindowTitle("d3");
    d3->setWindowFlags(Qt::WindowStaysOnTopHint);
    d3->show();
}



void MainWindow::on_pushButton444_clicked()
{

}
