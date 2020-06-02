#include "stringwheelwidget.h"

StringWheelWidget::StringWheelWidget(bool touch)
    : AbstractWheelWidget(touch)
{ }

QStringList StringWheelWidget::items() const
{
    return m_items;
}

void StringWheelWidget::setItems(const QStringList &items)
{
    m_items = items;
    if (m_currentItem >= items.count())
        m_currentItem = items.count()-1;
    update();
}


QSize StringWheelWidget::sizeHint() const
{
    // determine font size
    QFontMetrics fm(font());

    return QSize( fm.width("m") * 10 + 6, fm.height() * 7 + 6 );
}

QSize StringWheelWidget::minimumSizeHint() const
{
    QFontMetrics fm(font());

    return QSize( fm.width("m") * 5 + 6, fm.height() * 3 + 6 );
}

void StringWheelWidget::paintItem(QPainter* painter, int index, const QRect &rect)
{
    painter->setFont(QFont("Times", 20));
    //拿到纵坐标，如果纵坐标离中心位置越远则字体越小
    int y = rect.y();
    int fontSize = font().pointSize();  //相当于中间字体
    int centery = height()/2 - fontSize/2;  //中心y坐标
    int shift = std::abs(y-centery) / fontSize;
    fontSize -= shift*2;  //每隔一个字体减小2个像素
    painter->setFont(QFont("Times", fontSize));
//    painter->setPen(QPen(Qt::black, 100-shift*4));  //越远画笔越细
    int alpha = 255-shift*50;
    alpha = alpha<0? 5:alpha;
    painter->setPen(QPen(QColor(0,0,0,alpha)));  //越远透明度越高


    painter->drawText(rect, Qt::AlignCenter, m_items.at(index));
}

int StringWheelWidget::itemHeight() const
{
    QFontMetrics fm(font());
    return fm.height();
}

int StringWheelWidget::itemCount() const
{
    return m_items.count();
}


QString StringWheelWidget::currentContent() const
{
    return m_items.at(currentIndex());
}
