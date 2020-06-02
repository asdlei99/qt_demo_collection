#ifndef MYGRAPHICSITEM_H
#define MYGRAPHICSITEM_H

#include <QPixmap>
#include <QRectF>
#include <QGraphicsItem>

class MyGraphicsItem:public QGraphicsItem
{
public:
    MyGraphicsItem();
    MyGraphicsItem(const QString &fileName);
    ~MyGraphicsItem();
    QRectF boundingRect() const;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap *pix;
};

#endif // MYGRAPHICSITEM_H
