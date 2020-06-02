#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    AppInit();
    m_pMyThreadA = new myThreadA("11111111111111111111", 100); //设置线程打印11111111111111111111，线程休眠间隔100ms
    m_pMyThreadA->setParent(this);
    m_pMyThreadB = new myThreadA("22222222222222222222", 100);
    m_pMyThreadB->setParent(this);
    m_pMyThreadC = new myThreadA("33333333333333333333", 100);
    m_pMyThreadC->setParent(this);

}

Widget::~Widget()
{
    m_pMyThreadA->terminate();
    m_pMyThreadB->terminate();
    m_pMyThreadC->terminate();

    if(m_pMyThreadA != NULL)
    {
        delete m_pMyThreadA;
        m_pMyThreadA = NULL;
    }
    if(m_pMyThreadB != NULL)
    {
        delete m_pMyThreadB;
        m_pMyThreadB = NULL;
    }
    if(m_pMyThreadC != NULL)
    {
        delete m_pMyThreadC;
        m_pMyThreadC = NULL;
    }
    delete ui;
}

void Widget::on_BtnA_clicked()
{
    m_bThreadA = !m_bThreadA;
    ColorStateShow(ui->labelA, m_bThreadA);
    if(m_bThreadA)
    {
        m_pMyThreadA->start();
    }
    else
    {
        m_pMyThreadA->terminate();
    }
}

void Widget::on_BtnB_clicked()
{
    m_bThreadB = !m_bThreadB;
    ColorStateShow(ui->labelB, m_bThreadB);
    if(m_bThreadB)
    {
        m_pMyThreadB->start();
    }
    else
    {
        m_pMyThreadB->terminate();
    }
}

void Widget::on_Btnc_clicked()
{
    m_bThreadC = !m_bThreadC;
    ColorStateShow(ui->labelC, m_bThreadC);
    if(m_bThreadC)
    {
        m_pMyThreadC->start();
    }
    else
    {
        m_pMyThreadC->terminate();
    }
}

void Widget::AppInit()
{
    m_bThreadA = false;
    m_bThreadB = false;
    m_bThreadC = false;
}

void Widget::ColorStateShow(QLabel *lb, bool nb)
{
    if(nb)
    {
        lb->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else
    {
        lb->setStyleSheet("background-color: rgb(255, 0, 0);");
    }
}

//这个函数被子线程run所调用，用来打印输出显示父类传给子线程的文本参数
void Widget::SetMyText(QString str)
{
    ui->textEdit->append(str);
}

void Widget::on_pushButton_clicked()
{
    ui->textEdit->clear();
}

void Widget::on_pushButton_2_clicked()
{
    close();
}
