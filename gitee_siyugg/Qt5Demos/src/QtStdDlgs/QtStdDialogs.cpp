#include "QtStdDialogs.h"
#include "InputDialog.h"
#include "InforDialog.h"
#include "ui_QtStdDialogs.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>

QtStdDialogs::QtStdDialogs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtStdDialogs)
{
    ui->setupUi(this);
}

QtStdDialogs::~QtStdDialogs()
{
    delete ui;
}

void QtStdDialogs::on_fileDiaBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"返回文件名","/home/jisiyu/src/","C++ file(*.cpp);;C++头文件(*.h *.hpp *.hxx);;所有文件(*)",0,QFileDialog::HideNameFilterDetails);
    ui->fileDisplay->setText(fileName);
}

void QtStdDialogs::on_colorDiaBtn_clicked()
{
    QColor color = QColorDialog::getColor();
    if (color.isValid())
        ui->colorDisplay->setPalette(QPalette(color));
}

void QtStdDialogs::on_fontDiaBtn_clicked()
{
    QFont font;
    bool ok;
    font = QFontDialog::getFont(&ok);
    if (ok)
    {
        ui->fontDisplay->setFont(font);
    }
}

void QtStdDialogs::on_fontDiaBtn_2_clicked()
{
    InputDialog input(this);
    input.exec();
}

void QtStdDialogs::on_pushButton_clicked()
{
    InforDialog inforDia(this);
    inforDia.exec();
}
