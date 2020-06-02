#include "customplottest.h"
#include <QVector>

CustomplotTest::CustomplotTest(QWidget *parent) :
    QMainWindow(parent)
{
    QCustomPlot *customPlot = new QCustomPlot(this);
    customPlot->setFixedSize(300, 300);
    //可变数组存放绘图的坐标的数据，分别存放x和y坐标的数据，101为数据长度
    QVector<double> x(101), y(101);
    //添加数据，这里演示y=x^3，为了正负对称，x从-10到+10
    for (int i = 0; i<101; i++)
    {
        x[i] = i/5 - 10;
        y[i] = qPow(x[i], 3);//x的y次方;
    }
    //向绘图区域QCustomPlot添加一条曲线
    customPlot->addGraph();
    //添加数据
    customPlot->graph(0)->setData(x, y);
    //设置坐标轴名称
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    //设置坐标轴显示范围，否则只能看到默认范围
    customPlot->xAxis->setRange(-11, 11);
    customPlot->yAxis->setRange(-1100, 1100);

    this->setFixedSize(300, 300);
}
