#include "splitterdialog.h"
#include "ui_splitterdialog.h"

splitterDialog::splitterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::splitterDialog)
{
    ui->setupUi(this);
}

splitterDialog::~splitterDialog()
{
    delete ui;
}
