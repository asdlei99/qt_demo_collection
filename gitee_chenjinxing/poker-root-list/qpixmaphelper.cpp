#include "qpixmaphelper.h"

#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QSize>
#include <QtMath>

QPixmapHelper::QPixmapHelper()
{

}
QPixmap QPixmapHelper::PixmapToRound(QPixmap &src, int radius)
{
    //新建圆形遮罩层
    QSize size(2*radius,2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    //渲染设置
    painter.setRenderHint(QPainter::Antialiasing);          //抗锯齿
    painter.setRenderHint(QPainter::SmoothPixmapTransform); //平滑像素变换
    //绘制遮罩层
    painter.fillRect(0,0,size.width(),size.height(),Qt::white);
    painter.setBrush(QColor(0,0,0));
    painter.drawRoundedRect(0,0,size.width(),size.height(),99,99);


    //给资源添加圆形遮罩
    QPixmap rtn = src.scaled(size);
    rtn.setMask(mask);
    return rtn;
}

QPixmap QPixmapHelper::PixmapToTriangle(QPixmap &src, int side)
{
    //新建三角形遮罩层
    QSize size(side,side);
    QBitmap mask(size);
    QPainter painter(&mask);
    //根据变成确定三角形三个顶点
    static qreal ratioH =sqrt(3)/2;
    qreal h =ratioH* side;
    QPointF points[3]={
                        QPointF(side/2.0f, 0.0),
                        QPointF(0.0, h),
                        QPointF(side, h)
                        };
    //渲染设置
    painter.setRenderHint(QPainter::Antialiasing);          //抗锯齿
    painter.setRenderHint(QPainter::SmoothPixmapTransform); //平滑像素变换
    //绘制遮罩层
    painter.fillRect(0,0,size.width(),size.height(),Qt::white);
    painter.setBrush(QColor(0,0,0));
    //painter.drawRoundedRect(0,0,size.width(),size.height(),99,99);
    painter.drawPolygon(points,3);


    //给资源添加圆形遮罩
    QPixmap rtn = src.scaled(size);
    rtn.setMask(mask);
    return rtn;

}
