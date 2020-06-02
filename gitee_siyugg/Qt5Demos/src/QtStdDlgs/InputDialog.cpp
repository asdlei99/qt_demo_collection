#include "InputDialog.h"
#include "ui_InputDialog.h"
#include <QInputDialog>

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
}

InputDialog::~InputDialog()
{
    delete ui;
}

void InputDialog::on_nameModBtn_clicked()
{
    bool ok;
    QString name =  QInputDialog::getText(this,"修改姓名","输入新名字",QLineEdit::Normal,"修改名字",&ok);
    if (ok && !name.isEmpty() && (name != "修改姓名"))
        ui->nameDisplay->setText(name);
}

void InputDialog::on_sexModBtn_clicked()
{
    const static QStringList sexList{"男","女"};
    bool ok;
    QString sex = QInputDialog::getItem(this,"修改性别","修改性别",sexList,0,false,&ok);
    if (ok)
        ui->sexDisplay->setText(sex);
}

void InputDialog::on_mathModBtn_clicked()
{
    bool ok;
    QString mathGradeStr;
    double mathGrade = QInputDialog::getDouble(this,"数学成绩","修改成绩",0.0,0.0,100.0,1,&ok);
    if (ok)
        ui->mathDisplay->setText(mathGradeStr.setNum(mathGrade));
}

void InputDialog::on_literalModBtn_clicked()
{
    bool ok;
    QString literalGradeStr;
    int literalGrade = QInputDialog::getInt(this,"语文成绩","修改成绩",0,0,100,1,&ok);
    if (ok)
        ui->literalDisplay->setText(literalGradeStr.setNum(literalGrade));
}
