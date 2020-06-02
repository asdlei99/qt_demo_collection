#include "CircleWait.h"
#include <QPainter>
#include <QTimer>

CircleWait::CircleWait(QWidget *parent) : QWidget(parent),
    m_color(Qt::black),
    m_clockwiseRotate(true),
    m_rotateDelta(36),
    m_rotateAngle(0)
{
    m_timer = new QTimer;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(update()));
    m_timer->start(100);
}


void CircleWait::setColor(QColor color)
{
    if(color != m_color)
    {
        m_color = color;
        update();
    }
}

void CircleWait::setClockwiseRotate(bool clockwise)
{
    if(clockwise != m_clockwiseRotate)
    {
        m_clockwiseRotate = clockwise;
        update();
    }
}

void CircleWait::setRotateDelta(int delta)
{
    if(delta != m_rotateDelta)
    {
        m_rotateDelta = delta;
        update();
    }
}

void CircleWait::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width()/2, height()/2);
    int side = qMin(width(), height());
    painter.scale(side/100.0, side/100.0);

    painter.rotate(m_rotateAngle);
    drawCircleWait(painter);
    m_rotateAngle += m_clockwiseRotate?m_rotateDelta:-m_rotateDelta;
    m_rotateAngle %= 360;
}

void CircleWait::drawCircleWait(QPainter &painter)
{
    //根据100*100的大小进行画,在paintEvent中进行过缩放
    painter.save();
    painter.setPen(Qt::NoPen);
    QColor color = m_color;
    for (int i = 0; i <= 10; i++) {
        color.setAlphaF(1.0 * i/10);
        painter.setBrush(QBrush(color));
        painter.drawEllipse(30, -10, 20, 20);
        painter.rotate(36);
    }
    painter.restore();
}
