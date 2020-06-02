#include "ProgressBar.h"
#include "ui_ProgressBar.h"

ProgressBar::ProgressBar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressBar)
{
    ui->setupUi(this);
}

ProgressBar::~ProgressBar()
{
    delete ui;
}

void ProgressBar::on_startButton_clicked()
{
    for (int i = 0;i <= 10;++i)
        for (int j = 0;j <= 10000000;++j)
            ui->progressBar->setValue(i * 10);
    ui->startButton->setText(tr("此轮循环结束，点击重新开始"));
}
