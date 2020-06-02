#ifndef CARDRULE_H
#define CARDRULE_H
#include <QVector>
#include "card.h"

//牌型
typedef struct CardPlay
{
    CardPoint point;
    CardType type;
    quint16 len;

}CardPlay;


class CardRule
{
private:
    static CardRule *_rule;
    CardPoint _basePoint;
    CardType _baseType;
    quint16 _baseLength;

protected:
    QVector<CardPoint> _oneCard;
    QVector<CardPoint> _twoCards;
    QVector<CardPoint> _threeCards;
    QVector<CardPoint> _fourCards;
public:
    CardRule();
    static CardRule *getInstance();

    void sort(QVector<Card> *cards); //将牌进行排序
    void classifyCardType(QVector<Card> &cards); //按牌型分类
    void judgeCardType(); //判断牌型
    bool canPickCard(QVector<Card> &pre, quint16 pid, QVector<Card> &cur, quint16 cid);//判断是否可以出牌

    CardPoint basePoint() const;
    CardType baseType() const;
    quint16 baseLength() const;
};

#endif // CARDRULE_H
