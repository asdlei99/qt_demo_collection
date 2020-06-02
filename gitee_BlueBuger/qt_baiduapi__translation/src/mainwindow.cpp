#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "rqtranslator.h"

#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
		//appid  apikey
    rQTranslator trans("","");
    auto r = trans.translation("apple");
    if(r.first == true)
    {
        qDebug() << r.second.toStdString().c_str();
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}
