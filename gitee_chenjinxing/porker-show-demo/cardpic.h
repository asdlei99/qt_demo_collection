#ifndef CARDPIC_H
#define CARDPIC_H

#include <QLabel>
#include "card.h"


class CardPic : public QLabel
{
    Q_OBJECT
public:
    explicit CardPic(QWidget *parent = 0);

    void setPic(const QPixmap& pic, const QPixmap& back);
    QPixmap getpic();

    void setCard(Card card);
    Card getCard(void);

    void setSelected(bool selected);
    bool isSelected(void);

    void setFrontSide(bool frontSide);
    bool isFrontSide(void);

    void setCurrOwned(bool currowned);
    bool isCurrOwned(void);

    QPixmap backpic() const;
    void setBackpic(const QPixmap &backpic);

protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);

signals:
    void cardpicMousePress(CardPic* cardpic);

public slots:

private:
    QPixmap _pic;
    QPixmap _backpic;
    Card _card;

    bool _selected;   // 是否被选中
    bool _frontSide;  // 是否显示正面

    bool _currOwned;  // 是否是当前用户拥有


};

#endif // CARDPIC_H
