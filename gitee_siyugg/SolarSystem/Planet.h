#ifndef PLANET_H
#define PLANET_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QRectF>
#include <QTimerEvent>
#include <QObject>

class Planet:public QObject,public QGraphicsPixmapItem
{
public:
    Planet(QGraphicsItem *parent = nullptr);
    Planet(const QPixmap & pixmap,qreal _orbit,qreal  _revolution,QGraphicsItem * parent = nullptr);
    void setOrbitRadius(qreal value);
    void setRevolution(qreal value);
    void setSelfRadius(qreal value);
    void setAnglePerSec();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void timerEvent(QTimerEvent *);
private:
    qreal orbitRadius;
    qreal selfRadius;
    qreal anglePerSec;
    qreal revolutionPeriod;
    qreal x{0.0},y{0.0};
    qreal currentAngle{0.0};
};

#endif // PLANET_H
