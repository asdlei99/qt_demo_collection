#include "form.h"
#include "ui_form.h"
#include "sqlitequery.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setLayout(ui->mainLayout);

}

Form::~Form()
{
    delete ui;
}

void Form::on_addButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    QString passwd = ui->passwdLineEdit->text();

    QStringList list;
    list.append(name);
    list.append(passwd);

    SqliteQuery::instance()->insert(list);
}

void Form::on_delButton_clicked()
{

}

void Form::on_freshButton_clicked()
{
    SqliteQuery::instance()->fresh();
}
