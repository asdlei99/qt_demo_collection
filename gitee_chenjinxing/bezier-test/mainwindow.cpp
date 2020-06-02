#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bezierwgt.h"
#include "bezierfixwgt.h"
#include "bezierstdwgt.h"
#include "beziernorderwgt.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //BezierWgt * bezierWgt =new BezierWgt();
    //BezierFixWgt  * bezierWgt =new BezierFixWgt();
    //BezierStdWgt  * bezierWgt =new BezierStdWgt();
    BezierNOrderWgt * bezierWgt =new BezierNOrderWgt();
    this->setCentralWidget(bezierWgt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug("asdf");

//    BezierWgt * bezierWgt =new BezierWgt(this);
//    bezierWgt->setModal(false);
//    bezierWgt->setAttribute(Qt::WA_DeleteOnClose);
//    bezierWgt->show();
}
