#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class CalculatorWindow;
}

class CalculatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalculatorWindow(QWidget *parent = 0);
    ~CalculatorWindow();

public slots:
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();
    void on_btn_0_clicked();
    void on_btn_add_clicked();
    void on_btn_sub_clicked();
    void on_btn_mul_clicked();
    void on_btn_div_clicked();
    void on_btn_dot_clicked();
    void on_btn_back_clicked();
    void on_btn_clr_clicked();
    void on_btn_eql_clicked();
    void on_btn_lp_clicked();
    void on_btn_rp_clicked();

private:
    Ui::CalculatorWindow *ui;
    QString fomula;

    bool lastCharIsOperator() const;
};

#endif // CALCULATORWINDOW_H
