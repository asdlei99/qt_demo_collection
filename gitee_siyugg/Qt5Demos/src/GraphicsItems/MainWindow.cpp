#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QGraphicsScene>
#include <qmath.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),myItem(new MyGraphicsItem),currentAngle(0),currentScaleValue(1),currentShearValue(0),currentTranslateValue(0)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    //ui->graphicsView->setViewport();
    //scene->setSceneRect(-200,-200,400,400);
    ui->graphicsView->setMinimumSize(400,400);

    ui->rotateSlider->setRange(0,360);
    ui->scaleSlider->setRange(0,10);
    ui->shearSlider->setRange(0,10);
    ui->translateSlider->setRange(0,100);

    connect(ui->openImg,SIGNAL(triggered()),this,SLOT(slot_openImg()));
    connect(ui->quitAct,SIGNAL(triggered()),this,SLOT(slot_quit()));
    connect(ui->rotateSlider,SIGNAL(valueChanged(int)),this,SLOT(slot_rotate(int)));
    connect(ui->scaleSlider,SIGNAL(valueChanged(int)),this,SLOT(slot_scale(int)));
    connect(ui->shearSlider,SIGNAL(valueChanged(int)),this,SLOT(slot_shear(int)));
    connect(ui->translateSlider,SIGNAL(valueChanged(int)),this,SLOT(slot_translate(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_openImg()
{
    QString imgFileName = QFileDialog::getOpenFileName(this,"选择图片","/home/图片","图片(*.jpg *.png *.bmp);;所有文件(*)");
    if (!imgFileName.isEmpty())
    {
        QPixmap tmp(imgFileName);
        scene->setSceneRect(-tmp.width() / 2,-tmp.height() / 2,tmp.width(),tmp.height());
        myItem = new MyGraphicsItem(imgFileName);
        scene->clear();
        scene->addItem(myItem);
    }
}
void MainWindow::slot_quit()
{
    close();
}
void MainWindow::slot_rotate(int angle)
{
    ui->rotateLabel->setNum(angle);
    ui->graphicsView->rotate(angle - currentAngle);
    currentAngle = angle;
}
void MainWindow::slot_scale(int value)
{
    ui->scaleLabel->setNum(value);
    qreal s;
    if (value > currentScaleValue)
        s = pow(1.1,value - currentScaleValue);
    else s = pow(1/1.1,currentScaleValue - value);
    ui->graphicsView->scale(s,s);
    currentScaleValue = value;
}
void MainWindow::slot_shear(int value)
{
    ui->shearLabel->setNum(value);
    ui->graphicsView->shear((value - currentShearValue) / 10.0,0);
    currentShearValue = value;
}
void MainWindow::slot_translate(int value)
{
    ui->translateLabel->setNum(value);
    ui->graphicsView->translate(value - currentTranslateValue,value - currentTranslateValue);
    currentTranslateValue = value;
}
