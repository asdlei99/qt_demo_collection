#include "cardrule.h"
#include <QDebug>

CardRule *CardRule::_rule = NULL;

CardPoint CardRule::basePoint() const
{
    return _basePoint;
}

CardType CardRule::baseType() const
{
    return _baseType;
}

quint16 CardRule::baseLength() const
{
    return _baseLength;
}

CardRule::CardRule()
{
}

CardRule *CardRule::getInstance()
{
    if(_rule == NULL)
    {
        _rule = new CardRule();
    }

    return _rule;
}

void CardRule::sort(QVector<Card> *cards)
{
    qSort(cards->begin(),cards->end(),qGreater<Card>());

}

void CardRule::classifyCardType(QVector<Card> &cards)
{
    int *cardRecord = new int[Card_End];
    memset(cardRecord,0,sizeof(int)*Card_End);

    //记录重复牌的个数
    for(int i = 0;i < cards.size();i++)
    {
        int point = (CardPoint)cards.at(i).point;
        cardRecord[point]++;
    }

    _oneCard.clear();
    _twoCards.clear();
    _threeCards.clear();
    _fourCards.clear();

    //用一个一位数组记录牌，索引为点数，值为牌的个数
    for(int po = Card_3;po < Card_End;po++)
    {
        if(cardRecord[po] == 1)
        {
            _oneCard.push_back((CardPoint)po);
        }
        else if(cardRecord[po] == 2)
        {
            _twoCards.push_back((CardPoint)po);
        }
        else if(cardRecord[po] == 3)
        {
            _threeCards.push_back((CardPoint)po);
        }
        else if(cardRecord[po] == 4)
        {
            _fourCards.push_back((CardPoint)po);
        }
    }

    delete[] cardRecord;

}

void CardRule::judgeCardType()
{
    _basePoint = Card_Begin;
    _baseType = Card_Unknown;
    _baseLength = 0;

    if(_oneCard.isEmpty() &&
       _twoCards.isEmpty() &&
       _threeCards.isEmpty() &&
       _fourCards.isEmpty())    //牌为空
    {
        _baseType = Card_Null;
    }
    else if(_oneCard.size() == 1 &&
       _twoCards.isEmpty() &&
       _threeCards.isEmpty() &&
       _fourCards.isEmpty())    //单牌
    {
        _basePoint = _oneCard.at(0);
        _baseType = Card_Single;
    }
    else if(_oneCard.isEmpty() &&
       _twoCards.size() == 1 &&
       _threeCards.isEmpty() &&
       _fourCards.isEmpty())    //对子
    {
        _basePoint = _twoCards.at(0);
        _baseType = Card_Pair;
    }
    else if(_oneCard.isEmpty() &&
       _twoCards.isEmpty() &&
       _threeCards.size() == 1 &&
       _fourCards.isEmpty())    //三个不带
    {
        _basePoint = _threeCards.at(0);
        _baseType = Card_Triple;
    }
    else if(_oneCard.size() == 1 &&
       _twoCards.isEmpty() &&
       _threeCards.size() == 1 &&
       _fourCards.isEmpty())    //三带一
    {
        _basePoint = _threeCards.at(0);
        _baseType = Card_Triple_Single;
    }
    else if(_oneCard.isEmpty()&&
       _twoCards.size() == 1 &&
       _threeCards.size() == 1 &&
       _fourCards.isEmpty())    //三带一对
    {
        _basePoint = _threeCards.at(0);
        _baseType = Card_Triple_Pair;
    }
    else if(_oneCard.isEmpty()&&
       _twoCards.isEmpty() &&
       _threeCards.size() == 2 &&
       _fourCards.isEmpty())   //飞机
    {
        qSort(_threeCards.begin(),_threeCards.end());
        if(_threeCards.at(1) - _threeCards.at(0) == 1 &&
           _threeCards.at(1) < Card_2)
        {
            _basePoint = _threeCards.at(0);
            _baseType = Card_Plane;
        }
    }
    else if(_oneCard.size() == 2&&
       _twoCards.isEmpty() &&
       _threeCards.size() == 2 &&
       _fourCards.isEmpty())   //飞机带两单
    {
        qSort(_threeCards.begin(),_threeCards.end());
        if(_threeCards.at(1) - _threeCards.at(0) == 1 &&
           _threeCards.at(1) < Card_2)
        {
            _basePoint = _threeCards.at(0);
            _baseType = Card_Plane_Two_Single;
        }
    }
    else if(_oneCard.isEmpty()&&
       _twoCards.size() == 1 &&
       _threeCards.size() == 2 &&
       _fourCards.isEmpty())   //飞机带一对
    {
        qSort(_threeCards.begin(),_threeCards.end());
        if(_threeCards.at(1) - _threeCards.at(0) == 1 &&
           _threeCards.at(1) < Card_2)
        {
            _basePoint = _threeCards.at(0);
            _baseType = Card_Plane_One_Single;
        }
    }
    else if(_oneCard.isEmpty()&&
       _twoCards.size() == 2 &&
       _threeCards.size() == 2 &&
       _fourCards.isEmpty())   //飞机带两对
    {
        qSort(_threeCards.begin(),_threeCards.end());
        if(_threeCards.at(1) - _threeCards.at(0) == 1 &&
           _threeCards.at(1) < Card_2)
        {
            _basePoint = _threeCards.at(0);
            _baseType = Card_Plane_Two_Single;
        }
    }
    else if(_oneCard.isEmpty() &&
            _twoCards.size() >= 3 &&
            _threeCards.isEmpty() &&
            _fourCards.isEmpty()) //连队
    {
        qSort(_twoCards.begin(),_twoCards.end());
        if(_twoCards.first() >= Card_3 &&
           _twoCards.last() < Card_2 &&
           _twoCards.last() - _twoCards.first() == (_twoCards.size()-1))
        {
            _basePoint = _twoCards.at(0);
            _baseType = Card_Seq_Pair;
            _baseLength = _twoCards.size();
        }
    }
    else if(_oneCard.size()>= 5 &&
            _twoCards.isEmpty() &&
            _threeCards.isEmpty() &&
            _fourCards.isEmpty()) //顺子
    {
        qSort(_oneCard.begin(),_oneCard.end());
        if(_oneCard.first() >= Card_3 &&
           _oneCard.last() < Card_2 &&
           _oneCard.last() - _oneCard.first() == (_oneCard.size()-1))
        {
            _basePoint = _oneCard.at(0);
            _baseType = Card_Seq_Single;
            _baseLength = _oneCard.size();
        }
    }
    else if(_oneCard.isEmpty() &&
       _twoCards.isEmpty() &&
       _threeCards.isEmpty() &&
       _fourCards.size() == 1)  //炸弹
    {
        _basePoint = _fourCards.at(0);
        _baseType = Card_Bomb;
    }
    else if(_oneCard.size() == 2 &&
       _twoCards.isEmpty() &&
       _threeCards.isEmpty() &&
       _fourCards.size() == 1)  //四带二单
    {
        _basePoint = _fourCards.at(0);
        _baseType = Card_Bomb_Two_Single;
    }
    else if(_oneCard.isEmpty() &&
       _twoCards.size() == 1 &&
       _threeCards.isEmpty() &&
       _fourCards.size() == 1)  //四带一对
    {
        _basePoint = _fourCards.at(0);
        _baseType = Card_Bomb_Pair;
    }
    else if(_oneCard.isEmpty() &&
       _twoCards.size()== 2 &&
       _threeCards.isEmpty() &&
       _fourCards.size() == 1)  //四带二对
    {
        _basePoint = _fourCards.at(0);
        _baseType = Card_Bomb_Two_Pair;
    }
    else if(_oneCard.size() == 2 &&
       _twoCards.isEmpty() &&
       _threeCards.isEmpty() &&
       _fourCards.isEmpty())  //王炸
    {
        qSort(_oneCard.begin(),_oneCard.end());
        if(_oneCard.at(0) == Card_SJ &&
           _oneCard.at(1) == Card_BJ)
        {
            _baseType = Card_Bomb_Jokers;
        }
    }


}

bool CardRule::canPickCard(QVector<Card> &pre, quint16 pid, QVector<Card> &cur, quint16 cid)
{
    CardPlay prePlay;
    CardPlay curPlay;

    //出牌为空，不合法
    if(cur.isEmpty())
    {
        return false;
    }

    this->classifyCardType(pre);
    this->judgeCardType();
    prePlay.point = this->basePoint();
    prePlay.type = this->baseType();
    prePlay.len = this->baseLength();

    this->classifyCardType(cur);
    this->judgeCardType();
    curPlay.point = this->basePoint();
    curPlay.type = this->baseType();
    curPlay.len = this->baseLength();

    //牌型不符合规则
    if(curPlay.type == Card_Unknown)
    {
        return false;
    }

    //类型相同，匹配长度相同，点数大于上家的可以出
    if(prePlay.type == curPlay.type &&
       prePlay.len == curPlay.len &&
       prePlay.point < curPlay.point)
    {
        return true;
    }
    //我方出的是王炸，可以出
    if(curPlay.type == Card_Bomb_Jokers)
    {
        return true;
    }
    //我方出的是炸弹，上家出的不是王炸和炸弹
    if(curPlay.type == Card_Bomb &&
       prePlay.type != Card_Bomb_Jokers &&
       prePlay.type != Card_Bomb)
    {
        return true;
    }


    //上家是王炸，不能出
    if(prePlay.type == Card_Bomb_Jokers)
    {
        //上家是自己，可以出牌
        if(pid == cid)
        {
            return true;
        }

        return false;
    }

    //上家是自己，可以出牌
    if(pid == cid)
    {
        return true;
    }


    if(pre.isEmpty())
    {
        return true;
    }
    return false;

}
