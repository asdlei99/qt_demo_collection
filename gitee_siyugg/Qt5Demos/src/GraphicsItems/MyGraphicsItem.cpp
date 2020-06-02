#include "MyGraphicsItem.h"
#include <QPainter>

MyGraphicsItem::MyGraphicsItem():QGraphicsItem(),pix(new QPixmap())
{

}

MyGraphicsItem::MyGraphicsItem(const QString &fileName):QGraphicsItem(),pix(new QPixmap(fileName))
{    
}
MyGraphicsItem::~MyGraphicsItem()
{
    delete pix;
}
QRectF MyGraphicsItem::boundingRect() const
{
    return QRectF(-pix->width() / 2,-pix->height() / 2,pix->width(),pix->height());
}
void MyGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(-pix->width() / 2,-pix->height() / 2,*pix);
}
