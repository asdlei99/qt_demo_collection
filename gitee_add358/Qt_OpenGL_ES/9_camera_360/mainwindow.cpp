#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "opengl_widget.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_openglWidget(new OpenGLWidget(this))
{
    ui->setupUi(this);
//    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    ui->verticalLayout->addWidget(m_openglWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_clicked()
{
    QString name = QFileDialog::getOpenFileName(this, tr("Choose Picture"), "/home/jake/Pictures",
                                                tr("Images (*.png *.xpm *.jpg)"));
    ui->lineEdit->setText(name);

    m_openglWidget->set_texture(name);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    m_openglWidget->set_active_cube(arg1);
}
