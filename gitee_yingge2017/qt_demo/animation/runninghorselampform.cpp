#include "runninghorselampform.h"
#include "ui_runninghorselampform.h"

RunningHorseLampForm::RunningHorseLampForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RunningHorseLampForm)
{
    ui->setupUi(this);

    QRect rectLeft(22,22,222,111);
    QRect rightLeft(22,22,222,111);
}

RunningHorseLampForm::~RunningHorseLampForm()
{
    delete ui;
}
