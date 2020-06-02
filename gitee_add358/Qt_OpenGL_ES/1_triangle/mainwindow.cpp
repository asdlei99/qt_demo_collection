#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "opengl_widget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);


    OpenGLWidget *openglWidget = new OpenGLWidget(this);

    ui->verticalLayout->addWidget(openglWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{

}
