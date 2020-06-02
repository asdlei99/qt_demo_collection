#include "md5wgt.h"
#include "ui_md5wgt.h"

#include <QCryptographicHash>
#include <QDebug>
#include <QRegExp>

Md5Wgt::Md5Wgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Md5Wgt)
{
    ui->setupUi(this);
}

Md5Wgt::~Md5Wgt()
{
    delete ui;
}


void Md5Wgt::on_pushButton_clicked()
{
    QByteArray reqBytes = ui->edit_str->toPlainText().toUtf8();

    qDebug() <<reqBytes;
    //md5加密
    QByteArray bytePwdMd5 = QCryptographicHash::hash(reqBytes, QCryptographicHash::Md5);
    QByteArray strPwdMd5 = bytePwdMd5.toHex(); //加密后的数据
    QByteArray byteArrayUrlEncode=strPwdMd5.toPercentEncoding(); //UrlEncode
    ui->edit_md5->setText(byteArrayUrlEncode);
}

void Md5Wgt::on_pushButton_2_clicked()
{
     ui->edit_str->setText(ui->edit_str_old->toPlainText().simplified().remove(QRegExp("\\s")));
}
