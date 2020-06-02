#include "cardpic.h"
#include <QPainter>
#include <QDebug>

CardPic::CardPic(QWidget *parent) :
    QLabel(parent)
{
    _selected = false;
    _frontSide = true;
    _currOwned = false;
}

void CardPic::setPic(const QPixmap &pic, const QPixmap &back)
{
    _pic = pic;
    _backpic = back;
    resize(pic.size());
    update();
}

QPixmap CardPic::getpic()
{
    return _pic;

}

void CardPic::setCard(Card card)
{
    _card = card;

}

Card CardPic::getCard()
{
    return _card;

}

void CardPic::setSelected(bool selected)
{
    _selected = selected;

}

bool CardPic::isSelected()
{
    return _selected;

}

void CardPic::setFrontSide(bool frontSide)
{
    _frontSide = frontSide;

}

bool CardPic::isFrontSide()
{
    return _frontSide;

}

void CardPic::setCurrOwned(bool currowned)
{
    _currOwned = currowned;
}

bool CardPic::isCurrOwned()
{
    return _currOwned;
}


// 绘制事件
void CardPic::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (_frontSide)
    {
        painter.drawPixmap(rect(), _pic);
    }
    else
    {
        painter.drawPixmap(rect(), _backpic);
    }
}

void CardPic::mousePressEvent(QMouseEvent *event)
{
    if (_currOwned)
    {
        if (_selected)
        {
            _selected = false;
        }
        else
        {
            _selected = true;
        }
        update();
        emit cardpicMousePress(this);
    }

    qDebug() << "mousePressEvent";
}
QPixmap CardPic::backpic() const
{
    return _backpic;
}

void CardPic::setBackpic(const QPixmap &backpic)
{
    _backpic = backpic;
}




