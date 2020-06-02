#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mydialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Window_triggered()
{
//    MyDialog m_dialog;

//    m_dialog.setModal (true);
//    m_dialog.exec ();

    m_dialog = new MyDialog(this);

    m_dialog->setModal (true);      //show 函数执行的 模态（主窗口不响应） 非模态（主窗口响应）
    m_dialog->show ();
}
