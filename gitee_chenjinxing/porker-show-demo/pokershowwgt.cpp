#include "pokershowwgt.h"

PokerShowWgt::PokerShowWgt(QWidget *parent)
    : QWidget(parent)
{
    this->resize(800,600);
    this->initCardPic();
    this->initWidget();
}

PokerShowWgt::~PokerShowWgt()
{

}

void PokerShowWgt::initWidget()
{
    sendCardBtn =new QPushButton(this);
    sendCardBtn->setGeometry(this->size().width()/2,10,40,20);
    sendCardBtn->setText("发牌");
    connect(sendCardBtn,SIGNAL(clicked(bool)),this,SLOT(sendCards()));
}

void PokerShowWgt::initCardPic()
{
    _cardSize = QSize(80, 105);
    QPixmap cardspic(":/img/cards.png");
    _cardBackPic = cardspic.copy(2*_cardSize.width(), 4*_cardSize.height(), _cardSize.width(), _cardSize.height());
    //初始化除了queen以外cardpic
    for (int suit = Suit_Begin+1, i=0; suit < Suit_End; suit++, i++)
    {
        for(int point=Card_Begin+1,j=0; point<Card_SJ; point++, j++)
        {
            Card card;
            card.point = (CardPoint)point;
            card.suit = (CardSuit)suit;
            cutCardPic(cardspic, j*_cardSize.width() , i*_cardSize.height(), card);
            AddCard((CardSuit)suit, (CardPoint)point);
        }
    }
    //初始化queen
    Card card;
    card.point = (CardPoint)Card_SJ;
    card.suit = Suit_Begin;
    cutCardPic(cardspic, 0, 4*_cardSize.height(), card);
    AddCard(Suit_Begin, Card_SJ);

    card.point = (CardPoint)Card_BJ;
    card.suit = Suit_Begin;
    cutCardPic(cardspic, _cardSize.width(), 4*_cardSize.height(), card);
    AddCard(Suit_Begin, Card_BJ);
}
void PokerShowWgt::AddCard(CardSuit suit, CardPoint point)
{
    Card card;
    card.suit = suit;
    card.point = point;
    m_allCards.push_back(card);
}
// cardpic 定义
void PokerShowWgt::cutCardPic(QPixmap &cardspic, int x, int y, const Card & card)
{
    QPixmap pic = cardspic.copy(x, y, _cardSize.width(), _cardSize.height());

    CardPic* cardpic = new CardPic(this);
    cardpic->hide();
    cardpic->setPic(pic, _cardBackPic);
    cardpic->setCard(card);

    _cardpics.insert(card, cardpic);
}

void PokerShowWgt::sendCards()
{
    //高效洗牌;
    int nRandPos;
    Card cTempCard;
    QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    for(int k=0;k<54;k++)
    {
        //产生一个随机位置;
        nRandPos = qrand()%54;
        //把当前牌与这个随机位置的牌交换;
        cTempCard =m_allCards[k];
        m_allCards[k] =m_allCards[nRandPos];
        m_allCards[nRandPos] =cTempCard;
    }
    //发牌
    QVector<Card> oneCards;
    QVector<Card> twoCards;
    QVector<Card> threeCards;
    QVector<Card> backCards;
    for(int one =0;one <17;one ++)
        oneCards.push_back(m_allCards.at(one));
    for(int two =17;two <34;two ++)
        twoCards.push_back(m_allCards.at(two));
    for(int three =34;three <51;three ++)
        threeCards.push_back(m_allCards.at(three));
    //剩余三张牌
    backCards.push_back(m_allCards.at(51));
    backCards.push_back(m_allCards.at(52));
    backCards.push_back(m_allCards.at(53));

    //显示4列牌
    this->displayUserCards(oneCards,50);
    this->displayUserCards(twoCards,170);
    this->displayUserCards(threeCards,290);
    this->displayUserCards(backCards,410);
}
//在指定的高度位置显示手牌
void PokerShowWgt::displayUserCards(QVector<Card> &cards,int y)
{
    this->sort(&cards);
    QVector<CardPic*> cps(cards.size());
    for(int i=0;i<cards.length();i++){
        cps[i]=_cardpics[cards.at(i)];
        cps[i]->setCurrOwned(true);
        cps[i]->setGeometry(300+20*i,y,_cardSize.width(),_cardSize.height());
        cps[i]->raise();
        cps[i]->show();
        sleep(10);
    }
}

void PokerShowWgt::sort(QVector<Card> *cards)
{
    qSort(cards->begin(),cards->end(),qGreater<Card>());
}
void PokerShowWgt::sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
