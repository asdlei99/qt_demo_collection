#include "widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent) : QWidget(parent)
{

}

void Widget::set_image(const QImage &image)
{
    if (image.isNull()) {
        qDebug("%s(%s)[%d]", __FILE__, __func__, __LINE__);
        return;
    }
    m_image = image;
    update();
}

void Widget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawImage(0, 0, m_image);
    QWidget::paintEvent(e);
}
