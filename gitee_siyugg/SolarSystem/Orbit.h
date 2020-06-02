#ifndef ORBIT_H
#define ORBIT_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QColor>
#include <QRectF>

class Orbit:public QGraphicsEllipseItem
{
public:
    Orbit(QColor _color,QGraphicsItem *parent = nullptr);
    Orbit(QColor _color,int _x,int _y,int _width,int _height, QGraphicsItem *parent = nullptr);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
private:
    QColor color;
    int x,y;
    int width;
    int height;
};

#endif // ORBIT_H
