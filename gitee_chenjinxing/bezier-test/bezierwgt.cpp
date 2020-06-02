#include "bezierwgt.h"
#include <QPainter>
#include <QPainterPath>

BezierWgt::BezierWgt(QWidget *parent) : QWidget(parent),selectedPoint(nullptr)
{

}

void BezierWgt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    if(this->ctrlPoints.empty())
        return;

    for(int i=0;i <this->ctrlPoints.length() -1;i ++){
        painter.drawLine(this->ctrlPoints.at(i)->pos(),this->ctrlPoints.at(i+1)->pos());
    }

    QPainterPath mvPath;
    mvPath.moveTo(this->ctrlPoints.at(0)->pos());
    for(int i=0;i <this->ctrlPoints.length() -2;i++){
        mvPath.cubicTo(this->ctrlPoints.at(i)->pos(),
                       this->ctrlPoints.at(i+1)->pos(),
                       this->ctrlPoints.at(i+2)->pos());
    }
    painter.setPen(Qt::red);
    painter.drawPath(mvPath);
}

void BezierWgt::mousePressEvent(QMouseEvent *event)
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

void BezierWgt::mouseMoveEvent(QMouseEvent *event)
{
    if(this->selectedPoint ==nullptr)
        return;
    this->selectedPoint->move(event->pos());
    this->update();
}

void BezierWgt::mouseReleaseEvent(QMouseEvent *event)
{
    this->selectedPoint =nullptr;
}


bool BezierWgt::addCtrlPoint(const QPoint &p)
{
    QLabel *ctrlPoint =new QLabel(this);
    ctrlPoint->resize(10,10);
    ctrlPoint->move(p);
    ctrlPoint->setStyleSheet("QLabel{background:red}");
    ctrlPoint->setAttribute(Qt::WA_DeleteOnClose);
    ctrlPoint->show();
    this->ctrlPoints.append(ctrlPoint);

    return true;
}

bool BezierWgt::delCtrlPoint()
{
    this->ctrlPoints.last()->close();
    this->ctrlPoints.pop_back();
    return true;
}





