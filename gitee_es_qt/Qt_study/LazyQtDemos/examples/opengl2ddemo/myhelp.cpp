#include "myhelp.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

MyHelp::MyHelp()
{
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    background = QBrush(QColor(64, 32, 64));
    circleBrush = QBrush(QColor(255, 0, 0));
    circlePen = QPen(Qt::blue);
    circlePen.setWidth(1);
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);
}

void MyHelp::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    painter->fillRect(event->rect(), background);
    painter->translate(100, 100);

//! [2]
    painter->save();
    painter->setBrush(circleBrush);
    painter->setPen(circlePen);

    QPointF p1(0, 0);
    QPointF p2(-100, 100);
    painter->drawLine(p1, p2);

    painter->restore();
//! [2]

    painter->setPen(textPen);
    painter->setFont(textFont);
    painter->drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, QStringLiteral("Qt"));
}
