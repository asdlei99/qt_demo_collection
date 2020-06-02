#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "md5wgt.h"
#include "reqbatch.h"


#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QUrl>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->edit_url->setText("http://localhost:8080/MavenSSM/Services/api.action");
    ui->edit_post->setText("partnercode=1001&version=1.0.0&action=customerlogin&source=1&req={\"mobile\":\"13912345678\",\"password\":\"123456\"}&reqhash=3WPccIkeJpMAGj7jD0mmJQ%3d%3d");
    ui->radio_table->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//md5 dlg
void MainWindow::on_pushButton_clicked()
{
    Md5Wgt *wgt =new Md5Wgt();
    wgt->show();
}
//post
void MainWindow::on_pushButton_2_clicked()
{
    QString url =ui->edit_url->text();
    ReqBatch::Instance().setUrl(QUrl(url));
    ReqBatch::Instance().setWidget(this);
    QString str =ui->edit_post->toPlainText();
    auto str1 =str.toLatin1();
    auto str2 =str.toLocal8Bit();


    QTextCodec *tc = QTextCodec::codecForName("GBK");
    //QString tmpQStr = tc->toUnicode(str);
    //QByteArray bytes1 =tc->fromUnicode(str);

    QByteArray bytes1;
    bytes1 =str.toUtf8();
    bytes1 =str.toStdString().data();

    QByteArray data = ui->edit_post->toPlainText().toLatin1();
    data =str.toUtf8();
    if(ui->radio_json->isChecked())
        ReqBatch::Instance().executePostJson(data);
    else
        ReqBatch::Instance().executePostTable(data);
}

void MainWindow::showData(QByteArray &bytes)
{
    ui->edit_receive->setText(bytes);
}
