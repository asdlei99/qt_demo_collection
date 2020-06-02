#include "InforDialog.h"
#include "ui_InforDialog.h"
#include <QMessageBox>

InforDialog::InforDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InforDialog)
{
    ui->setupUi(this);
}

InforDialog::~InforDialog()
{
    delete ui;
}

void InforDialog::on_questionDia_clicked()
{
    switch(QMessageBox::question(this,"Questiong对话框","Do you know whar the hell you have done???",QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok))
    {
    case(QMessageBox::Ok):
        ui->content->setText("Do you know whar the hell you have done???:Ok");
        break;
    case(QMessageBox::Cancel):
        ui->content->setText("Do you know whar the hell you have done???:Cancel");
        break;
    default:
        break;
    }
}

void InforDialog::on_informationDia_clicked()
{
    switch(QMessageBox::information(this,"Information对话框","Don\'t forget before it is too late!!!",QMessageBox::Ok,QMessageBox::Ok))
    {
    case(QMessageBox::Ok):
        ui->content->setText("Information from Information Dialog:<b>Don\'t forget before it is too late!!!</b>");
    default:
        break;
    }
}

void InforDialog::on_warningDia_clicked()
{
    switch (QMessageBox::warning(this,"Warning对话框","You are stuck in something!!!",QMessageBox::Ok,QMessageBox::Ok))
    {
    case (QMessageBox::Ok):
        ui->content->setText("Information from Warning Dialog:<i>You are stuck in something!!!</i>");
        break;
    default:
        break;
    }
}

void InforDialog::on_criticalDia_clicked()
{
    switch (QMessageBox::critical(this,"Critical对话框","The dead is died!!!",QMessageBox::Ok,QMessageBox::Ok))
    {
    case (QMessageBox::Ok):
        ui->content->setText("Information from Critical Dialog:<strong>The dead is died!!!</strong>");
        break;
    default:
        break;
    }
}
void InforDialog::on_aboutDia_clicked()
{
    QMessageBox::about(this,"About对话框","I am no one.");
    ui->content->setText("Information from Critical Dialog:<strong>I am no one!!!</strong>");
}
void InforDialog::on_aboutQtDia_clicked()
{
    QMessageBox::aboutQt((this));
    ui->content->setText("Information from Critical Dialog:<strong>Qt is Great!!!</strong>");
}
void InforDialog::on_customDia_clicked()
{
    QMessageBox customDia;
    customDia.setWindowTitle(tr("Custom对话框"));
    customDia.setText("自定义对话框");
    customDia.setIconPixmap(QPixmap(":/icon/power.png").scaled(64,64));
    QPushButton *saveBtn = customDia.addButton(tr("save"),QMessageBox::ActionRole);
    QPushButton *discardBtn = customDia.addButton(tr("discard"),QMessageBox::ActionRole);
    QPushButton *cancelBtn = customDia.addButton(QMessageBox::Cancel);
    customDia.exec();
    QAbstractButton * clickedBtn = customDia.clickedButton();
    if (clickedBtn == saveBtn)
        ui->content->setText("Information from Custom Dialog:save is clicked!");
    else if (clickedBtn == discardBtn)
        ui->content->setText("Information from Custom Dialog:discard is clicked!");
    else if (clickedBtn == cancelBtn)
        ui->content->setText("Information from Custom Dialog:cancel is clicked!");
}
