#include "Square.h"
#include <windows.h>

Square::Square(QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &Square::slotTimer);
    m_timer->start(1000 / 33);
}

Square::~Square()
{
}

void Square::setCallbackFunc(void(*func) (QPointF point))
{
    m_callbackFunc = func;
}

QRectF Square::boundingRect() const
{
    return QRectF(-15, -15, 30, 30);
}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawRect(-15, -15, 30, 30);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Square::slotTimer()
{
    // ���ݰ�ť��������ƶ�������
    if (GetAsyncKeyState('A')) 
    {
        this->setX(this->x() - 2);
    }
    if (GetAsyncKeyState('D')) 
    {
        this->setX(this->x() + 2);
    }
    if (GetAsyncKeyState('W')) 
    {
        this->setY(this->y() - 2);
    }
    if (GetAsyncKeyState('S')) 
    {
        this->setY(this->y() + 2);
    }
    // ���ûص���������������λ��  �����ڷ��źŸ�mainwindow  ��mainwindowִ����Ӧ�ۺ���
    m_callbackFunc(this->pos());
}
