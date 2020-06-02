#include "DrawArea.h"
#include <QPixmap>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QCursor>

DrawArea::DrawArea(QWidget *parent) :
    QWidget(parent),pen(new QPen()),penColor(Qt::black),penWidth(1),penStyle(Qt::SolidLine),startPoint(),endPoint()
{
    setAutoFillBackground(true);
    setMinimumSize(600,400);
    pix = new QPixmap(size());
    pix->fill(Qt::white);
}
DrawArea::~DrawArea()
{
    delete pen;
    delete pix;
}

void DrawArea::setPenStyle(int _style)
{
    penStyle = static_cast<Qt::PenStyle>(_style);
}
void DrawArea::setPenColor(QColor _color)
{
    penColor = _color;
}
void DrawArea::setPenWidth(int _width)
{
    penWidth = _width;
}

void DrawArea::mousePressEvent(QMouseEvent * e)
{
    startPoint = e->pos();
}
void DrawArea::mouseMoveEvent(QMouseEvent * e)
{
    pen->setStyle(penStyle);
    pen->setColor(penColor);
    pen->setWidth(penWidth);

    QPainter tmpPainter(pix);
    //tmpPainter.begin(pix);
    tmpPainter.setPen(*pen);
    tmpPainter.drawLine(startPoint,e->pos());
    //tmpPainter.end();

    startPoint = e->pos();
    update();
}
void DrawArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),*pix);
}
void DrawArea::clear()
{
    QPixmap *newPix = new QPixmap(size());
    newPix->fill(Qt::white);
    delete pix;
    pix = newPix;
    update();
}

