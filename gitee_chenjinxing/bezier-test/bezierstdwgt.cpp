#include "bezierstdwgt.h"

#include <QPainter>
#include <QPainterPath>


BezierStdWgt::BezierStdWgt(QWidget *parent) : QWidget(parent)
{

}

void BezierStdWgt::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    if(this->ctrlPoints.empty())
        return;
    //绘制控制线段
    for(int i=0;i <this->ctrlPoints.length();i ++){
        painter.drawLine(this->ctrlPoints.at(i).leftCtrlPoint->pos(),
                         this->ctrlPoints.at(i).posiPoint->pos());
        painter.drawLine(this->ctrlPoints.at(i).rightCtrlPoint->pos(),
                         this->ctrlPoints.at(i).posiPoint->pos());
    }

    /*
     * 开始节点:当前节点
     * 控制点：当前节点的右控制点、下一个节点的左控制点
     * 终止点：下一个节点
    */
    QPainterPath mvPath;
    for(int i=0;i <this->ctrlPoints.length() -1;i++){
        mvPath.moveTo(this->ctrlPoints.at(i).posiPoint->pos());
        mvPath.cubicTo(this->ctrlPoints.at(i).rightCtrlPoint->pos(),
                       this->ctrlPoints.at(i+1).leftCtrlPoint->pos(),
                       this->ctrlPoints.at(i+1).posiPoint->pos());
    }
    painter.setPen(Qt::red);
    painter.drawPath(mvPath);
}

void BezierStdWgt::mousePressEvent(QMouseEvent *event)
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

void BezierStdWgt::mouseMoveEvent(QMouseEvent *event)
{
    if(this->selectedPoint ==nullptr)
        return;
    this->selectedPoint->move(event->pos());
    this->update();
}

void BezierStdWgt::mouseReleaseEvent(QMouseEvent *)
{
    this->selectedPoint =nullptr;
}



bool BezierStdWgt::addCtrlPoint(const QPoint &p)
{
    BezierPoint bPoint;
    bPoint.posiPoint      =this->createPoint(p,POSI_POINT_STYLE);
    bPoint.leftCtrlPoint  =this->createPoint(QPoint(p.x()-20,p.y()),LEFT_POINT_STYLE);
    bPoint.rightCtrlPoint =this->createPoint(QPoint(p.x()+20,p.y()),RIGHT_POINT_STYLE);
    this->ctrlPoints.append(bPoint);
    return true;
}

QLabel *BezierStdWgt::createPoint(const QPoint &p, const QString &style)
{
    QLabel *ctrlPoint =new QLabel(this);
    ctrlPoint->resize(10,10);
    ctrlPoint->move(p);
    ctrlPoint->setStyleSheet(style);
    //ctrlPoint->setAttribute(Qt::WA_DeleteOnClose);
    ctrlPoint->show();
    return ctrlPoint;
}

bool BezierStdWgt::delCtrlPoint()
{
    if(this->ctrlPoints.empty())
        return false;
    BezierPoint &bPoint =this->ctrlPoints.last();
    bPoint.posiPoint->close();
    bPoint.leftCtrlPoint->close();
    bPoint.rightCtrlPoint->close();
    this->ctrlPoints.pop_back();
    return true;
}





