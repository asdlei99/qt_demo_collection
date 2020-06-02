#include "calculatorwindow.h"
#include "ui_calculatorwindow.h"
#include "calc.h"
#include "operands.h"
#include <stdio.h>

CalculatorWindow::CalculatorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CalculatorWindow), fomula("0")
{
    ui->setupUi(this);
    this->setWindowTitle("Calculator");
    ui->edit_fomula->setText(fomula);
    ui->edit_fomula->selectAll();
}

CalculatorWindow::~CalculatorWindow()
{
    delete ui;
}

bool CalculatorWindow::lastCharIsOperator() const {
    QString lastChar = fomula.right(1);
    return lastChar == "+"
        || lastChar == "-"
        || lastChar == "*"
        || lastChar == "/"
        || lastChar == ".";
}

void CalculatorWindow::on_btn_1_clicked() {
    if (fomula != "0") {
        fomula.append('1');
    } else {
        fomula = "1";
    }
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_2_clicked() {
    if (fomula != "0") {
        fomula.append('2');
    } else {
        fomula = "2";
    }
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_3_clicked() {
    if (fomula != "0") {
        fomula.append('3');
    } else {
        fomula = "3";
    }
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_4_clicked() {
    if (fomula != "0") {
        fomula.append('4');
    } else {
        fomula = "4";
    }
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_5_clicked() {
    if (fomula != "0") {
        fomula.append('5');
    } else {
        fomula = "5";
    }
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_6_clicked() {
    if (fomula != "0") {
        fomula.append('6');
    } else {
        fomula = "6";
    }
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_7_clicked() {
    if (fomula != "0") {
        fomula.append('7');
    } else {
        fomula = "7";
    }
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_8_clicked() {
    if (fomula != "0") {
        fomula.append('8');
    } else {
        fomula = "8";
    }
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_9_clicked() {
    if (fomula != "0") {
        fomula.append('9');
    } else {
        fomula = "9";
    }
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_0_clicked() {
    if (fomula != "0") {
        fomula.append('0');
    } else {
        fomula = "0";
    }
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_add_clicked() {
    if (fomula != "0" && (!lastCharIsOperator())) {
        fomula.append('+');
    } else if (fomula == "0") {
        fomula = "+";
    }
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_sub_clicked() {
    if (fomula != "0" && (!lastCharIsOperator())) {
        fomula.append('-');
    } else if (fomula == "0") {
        fomula = "-";
    }
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_mul_clicked() {
    if (fomula != "0" && (!lastCharIsOperator())) {
        fomula.append('*');
    } else if (fomula == "0") {
        fomula = "*";
    }
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_div_clicked() {
    if (fomula != "0" && (!lastCharIsOperator())) {
        fomula.append('/');
    } else if (fomula == "0") {
        fomula = "/";
    }
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_dot_clicked() {
    if (fomula != "0" && (!lastCharIsOperator())) {
        fomula.append('.');
    } else if (fomula == "0") {
        fomula = ".";
    }
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_back_clicked() {
    fomula.chop(1);
    if (fomula.length() == 0) fomula = "0";
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_clr_clicked() {
    fomula = "0";
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_eql_clicked() {
    memcpy(expression, ui->edit_fomula->text().toStdString().c_str(), MAX_LENGTH);
    if (check()) {
        static char result[MAX_LENGTH] = {0};
        memset(result, 0, MAX_LENGTH);
        parse();
        sprintf(result, "%g", opr_pop());
        ui->label_result->setText(result);
    } else {
        ui->edit_fomula->setText("Error!");
        fomula = "0";
    }
    memset(expression, 0, MAX_LENGTH);
}
void CalculatorWindow::on_btn_lp_clicked() {
    fomula.append('(');
    ui->edit_fomula->setText(fomula);
}
void CalculatorWindow::on_btn_rp_clicked() {
    fomula.append(')');
    ui->edit_fomula->setText(fomula);
}
