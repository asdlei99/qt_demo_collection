#ifndef BEZIERNORDERWGT_H
#define BEZIERNORDERWGT_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QVector>
#include <QLabel>
#include <QPoint>
#include <QMap>

class BezierNOrderWgt : public QWidget
{
    Q_OBJECT
public:
    explicit BezierNOrderWgt(QWidget *parent = nullptr);

signals:

public slots:

//控制节点
private:
    QVector<QLabel*> ctrlPoints;
    QWidget *selectedPoint;

private:
    //重写函数
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);

    //添加节点
    bool addCtrlPoint(const QPoint &p);
    //删除节点
    bool delCtrlPoint();

public:
    //借用杨辉三角算法 ---------------------------
    /*
     * 计算杨辉三角
     * n代表第n行
     * coms代表第n行的每个数:C(n,i)组合数
     */
    static bool YhTriangle(int n,QVector<int> &coms);
    //获取n个贝塞尔曲线上的点 控制点为points，贝塞尔的点位bzPoints
    static bool getPoints(int n,QVector<QPoint> &points,QVector<QPoint> &bzPoints);


    //直接套公式算法  ----------------------------
    //存储阶乘 避免二次计算
    static QMap<int,long> factorials;
    //存储C(n,m)的组合数 避免二次计算 key值为"n_m"的形式
    static QMap<QString,long> combinations;

    static long getFactorial(int n);
    static long getCombination(int n,int m);
    //求阶乘
    static long factorialCalc(int n);
    //求组合数
    static long combinationCalc(int n,int m);


};

#endif // BEZIERNORDERWGT_H
