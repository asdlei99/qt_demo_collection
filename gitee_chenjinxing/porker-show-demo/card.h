#ifndef CART_H
#define CART_H
enum CardPoint
{
    Card_Begin,

    Card_3,
    Card_4,
    Card_5,
    Card_6,
    Card_7,
    Card_8,
    Card_9,
    Card_10,
    Card_J,
    Card_Q,
    Card_K,
    Card_A,
    Card_2,

    Card_SJ,
    Card_BJ,

    Card_End
};

enum CardSuit
{
    Suit_Begin,

    Diamond,
    Spade,
    Heart,
    Club,

    Suit_End
};

enum CardType
{
    Card_Unknown,           //初始化类型
    Card_Null,               //空
    Card_Single,			// 单
    Card_Pair,				// 对

    Card_Triple,			// 三个
    Card_Triple_Single,		// 三带一
    Card_Triple_Pair,		// 三带二

    Card_Plane,				// 飞机，555_666
    Card_Plane_Two_Single,	// 飞机带单，555_666_3_4
    Card_Plane_One_Single,  // 飞机带一对，555_666_33
    Card_Plane_Two_Pair,	// 飞机带双，555_666_33_44

    Card_Seq_Pair,			// 连对，33_44_55(_66...)
    Card_Seq_Single,		// 顺子，34567(8...)

    Card_Bomb,				// 炸弹
    Card_Bomb_Pair,			// 炸弹带一对
    Card_Bomb_Two_Single,	// 炸弹带两单
    Card_Bomb_Two_Pair,	    // 炸弹带两对

    Card_Bomb_Jokers,			// 王炸
};
class Card
{
public:
    Card(int po,int su);
    Card();
    CardPoint point;
    CardSuit suit;
    CardPoint getPoint() const;
    void setPoint(const CardPoint &value);
    CardSuit getSuit() const;
    void setSuit(const CardSuit &value);
public:
    Card &operator=(const Card & right);

};

inline bool operator==(const Card& left, const Card& right)
{
    return (left.point == right.point && left.suit == right.suit);
}

inline bool operator<(const Card& left, const Card& right)
{
    if (left.point == right.point)
    {
        return left.suit < right.suit;
    }
    else
    {
        return left.point <right.point;
    }
}
#endif // CART_H
