#include "iconfactory.h"
#include <QPainter>
#include <QPainterPath>
#include <QIcon>
#include <QPixmap>
#include <QToolBar>
#include <QGridLayout>
#include <QToolButton>
#include <QMatrix>
#include <QBrush>
#include <QLinearGradient>

IconFactory::IconFactory()
{

}

void IconFactory::createAll()
{
    saveArrow();
    saveArc();
    saveZoomArrow();

    savePoint();
    saveLine();
    saveFace();
}

//绘制箭头
QPixmap IconFactory::saveArrow()
{
    QPixmap btnIcon1(100,100);
    btnIcon1.fill(Qt::transparent);
    QPainter painter1(&btnIcon1);
    QPainterPath painterPath1;
    painterPath1.moveTo(50,100);
    painterPath1.lineTo(50,30);
    painterPath1.lineTo(30,30);
    painterPath1.lineTo(50,0);
    painterPath1.lineTo(70,30);
    painterPath1.lineTo(50,30);
    painterPath1.lineTo(50,100);

    painter1.translate(50,50);
    painter1.rotate(45);
    painter1.translate(-50,-50);

    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::blue);
    QBrush brush;
    brush.setColor(Qt::blue);

    painter1.setPen(pen);
    painter1.setBrush(Qt::blue);
    painter1.drawPath(painterPath1);


    btnIcon1.save("arrow.png");

    return btnIcon1;
}

QPixmap IconFactory::saveArc()
{
    QPixmap btnIcon1(100,100);
    btnIcon1.fill(Qt::transparent);
    QPainter painter1(&btnIcon1);
    QPainterPath painterPath1;
    painterPath1.arcMoveTo(10,10,160,160,90);
    painterPath1.arcTo(10,10,160,160,90,90);

    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::blue);

    painter1.setPen(pen);
    painter1.drawPath(painterPath1);

    btnIcon1.save("arc.png");

    return btnIcon1;
}

QPixmap IconFactory::saveZoomArrow()
{
    QPixmap btnIcon1(100,100);
    btnIcon1.fill(Qt::transparent);
    QPainter painter1(&btnIcon1);
    QPainterPath painterPath1;
    painterPath1.moveTo(50,100);
    painterPath1.lineTo(50,30);
    painterPath1.moveTo(35,0);
    painterPath1.addRect(35,0,30,30);

    painter1.translate(50,50);
    painter1.rotate(45);
    painter1.translate(-50,-50);

    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::blue);
    QBrush brush;
    brush.setColor(Qt::blue);

    painter1.setPen(pen);
    painter1.setBrush(Qt::blue);
    painter1.drawPath(painterPath1);


    btnIcon1.save("zoom_arrow.png");

    return btnIcon1;
}

QPixmap IconFactory::savePoint()
{
    QPixmap btnIcon1(100,100);
    btnIcon1.fill(Qt::transparent);
    QPainter painter1(&btnIcon1);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter1.setBrush(Qt::gray);
    painter1.drawRect(10,10,80,80);

    pen.setWidth(8);
    pen.setColor(Qt::blue);
    painter1.setPen(pen);
    painter1.drawPoint(10,10);

    btnIcon1.save("point.png");
    return btnIcon1;
}

QPixmap IconFactory::saveLine()
{
    QPixmap btnIcon1(100,100);
    btnIcon1.fill(Qt::transparent);
    QPainter painter1(&btnIcon1);
    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::black);
    painter1.setBrush(Qt::gray);
    painter1.drawRect(10,10,80,80);

    pen.setWidth(4);
    pen.setColor(Qt::blue);
    painter1.setPen(pen);
    painter1.drawLine(10,10,10,90);

    btnIcon1.save("line.png");
    return btnIcon1;
}

QPixmap IconFactory::saveFace()
{
    QPixmap btnIcon1(100,100);
    btnIcon1.fill(Qt::transparent);
    QPainter painter1(&btnIcon1);
    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::blue);
    painter1.setBrush(Qt::blue);
    painter1.drawRect(10,10,80,80);

    btnIcon1.save("face.png");
    return btnIcon1;
}

