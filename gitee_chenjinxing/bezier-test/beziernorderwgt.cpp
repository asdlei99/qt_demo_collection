#include "beziernorderwgt.h"
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#include <QDebug>

QMap<int,long> BezierNOrderWgt::factorials;
//存储C(n,m)的组合数 避免二次计算 key值为"n_m"的形式
QMap<QString,long> BezierNOrderWgt::combinations;

BezierNOrderWgt::BezierNOrderWgt(QWidget *parent) : QWidget(parent)
{

}

void BezierNOrderWgt::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    if(this->ctrlPoints.empty())
        return;

    //贝塞尔曲线取点个数
    int bzNumber =0;
    //控制点
    QVector<QPoint> points;
    if(!this->ctrlPoints.empty())
        points.append(this->ctrlPoints.at(0)->pos());
    for(int i=1;i <this->ctrlPoints.size();i ++){
        //绘制线段
        painter.drawLine(this->ctrlPoints.at(i)->pos(),this->ctrlPoints.at(i-1)->pos());
        //添加到控制点
        points.append(this->ctrlPoints.at(i)->pos());
        //计算贝塞尔曲线取点个数bzNumber 这里用位置来计算 可以有其他的方法
        bzNumber += qAbs(this->ctrlPoints.at(i)->pos().x()-this->ctrlPoints.at(i-1)->pos().x());
    }

    if(points.size() <3){
        return;
    }

    //(int n, QVector<QPoint> &points, QVector<QPoint> &bzPoints)
    //曲线上的点
    QVector<QPoint> bzPoints;
    //获取贝塞尔曲线上的点
    BezierNOrderWgt::getPoints(bzNumber,points,bzPoints);

    QPainterPath mvPath;
    mvPath.moveTo(this->ctrlPoints.at(0)->pos());
    for(int i=0;i <bzPoints.length();i++){
        mvPath.lineTo(bzPoints.at(i));
    }
    painter.setPen(Qt::red);
    painter.drawPath(mvPath);
}

void BezierNOrderWgt::mousePressEvent(QMouseEvent *event)
{
    if(event->button() ==Qt::RightButton){
        this->delCtrlPoint();
        this->update();
    }
    else if(event->button() ==Qt::LeftButton){
        //如果点击位置有控件则选择控件 如果无控件就新增
        QWidget *w =this->childAt(event->pos());
        if(w==nullptr){
            this->addCtrlPoint(event->pos());
            this->update();
            return;
        }
        if(w->inherits("QLabel")){
            this->selectedPoint =w;
        }
    }
}

void BezierNOrderWgt::mouseMoveEvent(QMouseEvent *event)
{
    if(this->selectedPoint ==nullptr)
        return;
    this->selectedPoint->move(event->pos());
    this->update();
}

void BezierNOrderWgt::mouseReleaseEvent(QMouseEvent *)
{
    this->selectedPoint =nullptr;
}


bool BezierNOrderWgt::addCtrlPoint(const QPoint &p)
{
    QLabel *ctrlPoint =new QLabel(this);
    ctrlPoint->resize(10,10);
    ctrlPoint->move(p);
    ctrlPoint->setStyleSheet("QLabel{background:red}");
    //ctrlPoint->setAttribute(Qt::WA_DeleteOnClose);
    ctrlPoint->show();
    this->ctrlPoints.append(ctrlPoint);
    return true;
}

bool BezierNOrderWgt::delCtrlPoint()
{
    this->ctrlPoints.last()->close();
    this->ctrlPoints.pop_back();
    return true;
}
//获取指定数目的坐标点


//获取杨辉三角的第n行数据
bool BezierNOrderWgt::YhTriangle(int n, QVector<int> &coms)
{
    coms.clear();
    QVector<int> temp;
    for(int i =0;i <n;i++){
        temp =coms;
        if(i ==0){
            coms.append(1);
            temp.append(1);
            continue;
        }
        for(int j=1;j<i;j++){
            coms[j] =temp.at(j-1)+temp.at(j);
        }
        coms.append(1);
        temp.append(1);
    }
    return true;
}
//获取n个贝塞尔曲线上的点 控制点为points 贝塞尔的点为bzPoints
bool BezierNOrderWgt::getPoints(int n, QVector<QPoint> &points, QVector<QPoint> &bzPoints)
{
    bzPoints.clear();
    //控制点的数目number
    int number =points.size();
    //至少三个点才能绘制
    if(number<3)
        return false;
    //获取points个数的杨辉三角数据
    QVector<int> coms;
    BezierNOrderWgt::YhTriangle(number,coms);
    for(int i =0;i<n;i++){
        float t = (float) i/n;
        float tempx=0.0f;
        float tempy=0.0f;
        for(int k=0;k<number;k++){
            tempx +=qPow(1-t,number-k-1)*qPow(t,k)*coms.at(k)*points.at(k).x();
            tempy +=qPow(1-t,number-k-1)*qPow(t,k)*coms.at(k)*points.at(k).y();
        }
        bzPoints.append(QPoint(tempx,tempy));
    }

    return true;
}

//获取n的阶乘 如果已经计算过则直接返回 否则计算后保存
long BezierNOrderWgt::getFactorial(int n)
{
    if(BezierNOrderWgt::factorials.contains(n))
        return BezierNOrderWgt::factorials.find(n).value();

    long fac =BezierNOrderWgt::factorialCalc(n);
    BezierNOrderWgt::factorials.insert(n,fac);
    return fac;
}
//获取C(n,m)组合数 如果已经计算过则直接返回 否则计算后保存
long BezierNOrderWgt::getCombination(int n, int m)
{
    QString key =QString::number(n)+"_"+QString::number(n);
    if(BezierNOrderWgt::combinations.contains(key))
        return BezierNOrderWgt::combinations.find(key).value();
    long com =BezierNOrderWgt::combinationCalc(n,m);
    BezierNOrderWgt::combinations.insert(key,com);
    return com;
}

//求n的阶乘
long BezierNOrderWgt::factorialCalc(int n)
{
    if(n <1)
        return 0;
    long fac =1;
    for(int i =1;i <=n;i++)
        fac =fac* i;
    return fac;
}

//n里面取m个元素的取法 C(n,m) = n!/(m!*(n-m)!)
long BezierNOrderWgt::combinationCalc(int n, int m)
{
    long nf =BezierNOrderWgt::getFactorial(n);
    long mf  =BezierNOrderWgt::getFactorial(m);
    long nmf  =BezierNOrderWgt::getFactorial(n-m);
    return nf/(mf*nmf);
}




