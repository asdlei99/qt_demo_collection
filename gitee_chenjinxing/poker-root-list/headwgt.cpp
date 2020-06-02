#include "headwgt.h"
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QSize>
#include <QCursor>
#include <QMessageBox>

#include "qpixmaphelper.h"

HeadWgt::HeadWgt(QWidget *parent) : QWidget(parent)
{

}

void HeadWgt::paintEvent(QPaintEvent *)
{
    QPixmap showPix;
    if(!this->userName.isEmpty())
        showPix.load(":/img/qqHead.jpeg");
    else
        showPix.load(":/img/empty.jpg");
    QPixmap round =QPixmapHelper::PixmapToRound(showPix,30);
    QPainter painter(this);
    painter.drawPixmap(0,0,round);
    //painter.drawText(0,35,this->userName);
}

void HeadWgt::enterEvent(QEvent *)
{
    QCursor cursor;
    cursor.setShape(Qt::CursorShape::PointingHandCursor);
    this->setCursor(cursor);
}

void HeadWgt::leaveEvent(QEvent *)
{
    QCursor cursor;
    cursor.setShape(Qt::CursorShape::ArrowCursor);
    this->setCursor(cursor);
}

void HeadWgt::mousePressEvent(QMouseEvent *)
{
    //设置用户名
    QMessageBox::information(this,"事件","用户进入房间事件",QMessageBox::Ok);
}


QString HeadWgt::getUserName() const
{
    return userName;
}

void HeadWgt::setUserName(const QString &value)
{
    userName = value;
}

void HeadWgt::updateView()
{
    this->update();
}
