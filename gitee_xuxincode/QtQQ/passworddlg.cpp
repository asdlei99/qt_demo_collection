#include "passworddlg.h"
#include "ui_passworddlg.h"
#include "listwindow.h"
#include <QMessageBox>
#include <QTextCodec>
passworddlg::passworddlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::passworddlg)
{
    ui->setupUi(this);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    setWindowTitle(LOCAL("�޸�����"));
    ui->password->setEchoMode(QLineEdit::Password);
    ui->repassword->setEchoMode(QLineEdit::Password);
    connect(ui->bk_cancle,SIGNAL(clicked()),this,SLOT(cancle()));
    connect(ui->bt_ok,SIGNAL(clicked()),this,SLOT(modify()));
}

passworddlg::~passworddlg()
{
    delete ui;
}

void passworddlg::modify()
{
    QString password1 = ui->password->text();
    QString password2 = ui->repassword->text();

    if(password1.isEmpty() || password2.isEmpty())
    {
        QMessageBox::information(this,LOCAL("��ʾ"),LOCAL("���벻��Ϊ��"),0);
        return;
    }

    if(password1 == password2)
    {
        Listwindow::Instance()->setpassword(password1);
        this->close();
    }
    else
    {
        QMessageBox::information(this,LOCAL("��ʾ"),LOCAL("������������벻һ��"),0);
    }
}

void passworddlg::cancle()
{
    this->close();
}
