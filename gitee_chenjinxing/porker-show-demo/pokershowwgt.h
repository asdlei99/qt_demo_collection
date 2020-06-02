#ifndef POKERSHOWWGT_H
#define POKERSHOWWGT_H

#include <QWidget>
#include <QMap>
#include <QPixmap>
#include <QSize>
#include <QTime>
#include <QVector>
#include <QPushButton>

#include <QEventLoop>
#include <QCoreApplication>

#include "card.h"
#include "cardpic.h"

class PokerShowWgt : public QWidget
{
    Q_OBJECT

public:
    PokerShowWgt(QWidget *parent = 0);
    ~PokerShowWgt();

    //初始化界面控件
    void initWidget();
//控件
    QPushButton * sendCardBtn;
private:
    //cardpic的图片信息
    QPixmap _cardBackPic;  //背面图片
    QSize _cardSize;       //大小
    QMap<Card, CardPic*> _cardpics;
    //发牌
private:
    QVector<Card> m_allCards;
public:
    //初始化cardpic
    void initCardPic();

    //从(x,y)开始切割图片 新增一个cardpic
    void cutCardPic(QPixmap& cardspic, int x, int y,const Card &card);


    //初始化的时候新增到所有m_allCards
    void AddCard(CardSuit suit, CardPoint point);
    //排序
    void sort(QVector<Card> *cards);
    //从y位置开始打印牌
    void displayUserCards(QVector<Card> &cards,int y);

    //sleep
    void sleep(unsigned int msec);

public slots:
    //发牌逻辑 随机发牌成三组 并且剩余三张牌
    void sendCards();

};

#endif // POKERSHOWWGT_H
