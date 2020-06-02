#include "card.h"

Card::Card(int po, int su)
{
    this->point =CardPoint(po);
    this->suit =CardSuit(su);
}

Card::Card()
{
}
CardSuit Card::getSuit() const
{
    return suit;
}

void Card::setSuit(const CardSuit &value)
{
    suit = value;
}

Card &Card::operator=(const Card &right)
{
    if(this ==&right)
    {
        return *this;
    }
    point =right.getPoint();
    suit  =right.getSuit();
    return *this;
}

CardPoint Card::getPoint() const
{
    return point;
}

void Card::setPoint(const CardPoint &value)
{
    point = value;
}

