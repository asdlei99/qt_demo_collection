#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <mythreada.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


private slots:
    void on_BtnA_clicked();
    void on_BtnB_clicked();
    void on_Btnc_clicked();

private:
    Ui::Widget *ui;

    bool m_bThreadA;    //线程A的启停标志位
    bool m_bThreadB;    //线程B的启停标志位
    bool m_bThreadC;    //线程C的启停标志位

    myThreadA *m_pMyThreadA;
    myThreadA *m_pMyThreadB;
    myThreadA *m_pMyThreadC;

    void AppInit(); //函数变量初始化
    void ColorStateShow(QLabel *lb, bool nb);

private slots:
    void SetMyText(QString str);



    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // WIDGET_H
