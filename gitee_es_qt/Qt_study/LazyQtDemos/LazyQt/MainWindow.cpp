#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "excel/ReadExcel.h"
#include "model_view/ModelViewDialog.h"
#include "model_view/DialogMySelection.h"
#include "stardelegate/DialogStar.h"
#include "checkdelegate/DialogCheck.h"
#include "Utils.h"
#include <QDebug>
#include <QThread>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    radioButtonView = new LzRadioButtonView(this);
    dialogStar = new DialogStar(this);
    dialogCheck = new DialogCheck(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnReadExcel_clicked()
{
    ReadExcel readExcel;
    if (readExcel.openExcel(QStringLiteral("E:\\src_works\\qt\\es_qt\\Qt_study\\LazyQtDemos\\除尘设备IO.xlsx"))) {
        QString value = readExcel.getCellData(2, 2).toString();
        QString value2 = readExcel.getCellData(2, 3).toString();
        qDebug() << value << value2 << endl;
    }
}

void MainWindow::on_btnShowRadioView_clicked()
{
    if (radioButtonView) {
        radioButtonView->show();
    }
}


void MainWindow::on_pushButtonModelView_clicked()
{
    ModelViewDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_pushButtonMySelection_clicked()
{
    DialogMySelection dialog(this);
    dialog.exec();
}

void MainWindow::on_pushButtonStar_clicked()
{
    dialogStar->show();
}

void MainWindow::on_pushButtonCheck_clicked()
{
    dialogCheck->show();
}

void MainWindow::on_pushButtonSleep_clicked()
{
    // 测试qt sleep 和自己 写的 delay 的区别
    qDebug() << "Sleep " << QTime::currentTime().toString();
//    QThread::msleep(10000);
    Utils::delay(5000);
    qDebug() << "End sleep " << QTime::currentTime().toString();
    Utils::delay(3000);
    qDebug() << "End sleep " << QTime::currentTime().toString();

}

