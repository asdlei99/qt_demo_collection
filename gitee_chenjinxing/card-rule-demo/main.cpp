#include <QDebug>
#include <QCoreApplication>
#include "cardrule.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<Card> pre;//上一手牌
    QVector<Card> cur;//当前牌
    quint16 pid =12;  //上一手牌的打牌人ID
    quint16 cid =1112;//当前牌的打牌人ID

    //测试三个8带一个9  上一首牌是三个6带一个10  应该返回true
    pre.clear();
    pre.push_back(Card(Card_6,Heart));
    pre.push_back(Card(Card_6,Spade));
    pre.push_back(Card(Card_6,Diamond));
    pre.push_back(Card(Card_10,Heart));
    cur.clear();
    cur.push_back(Card(Card_8,Heart));
    cur.push_back(Card(Card_8,Spade));
    cur.push_back(Card(Card_8,Diamond));
    cur.push_back(Card(Card_9,Heart));
    qDebug()<<"\t"<<"三个8带一个9"<<"\t"<<"打"<<"\t"<<"三个6带一个10："
           <<"\t"<<CardRule::getInstance()->canPickCard(pre,pid,cur,cid);

    //测试炸弹4  上一首牌是三个8带一个9  应该返回true
    pre.clear();
    pre.push_back(Card(Card_8,Heart));
    pre.push_back(Card(Card_8,Spade));
    pre.push_back(Card(Card_8,Diamond));
    pre.push_back(Card(Card_9,Heart));
    cur.clear();
    cur.push_back(Card(Card_4,Heart));
    cur.push_back(Card(Card_4,Spade));
    cur.push_back(Card(Card_4,Diamond));
    cur.push_back(Card(Card_4,Club));
    qDebug()<<"\t"<<"四个4即炸弹4"<<"\t"<<"打"<<"\t"<<"三个8带一个9："<<"\t"
           <<CardRule::getInstance()->canPickCard(pre,pid,cur,cid);

    //测试飞机666777  上一首牌是三个8带一个9  应该返回false
    pre.clear();
    pre.push_back(Card(Card_8,Heart));
    pre.push_back(Card(Card_8,Spade));
    pre.push_back(Card(Card_8,Diamond));
    pre.push_back(Card(Card_9,Heart));
    cur.clear();
    cur.push_back(Card(Card_6,Heart));
    cur.push_back(Card(Card_6,Spade));
    cur.push_back(Card(Card_6,Diamond));
    cur.push_back(Card(Card_7,Club));
    cur.push_back(Card(Card_7,Diamond));
    cur.push_back(Card(Card_7,Spade));
    qDebug()<<"\t"<<"飞机666777"<<"\t"<<"打"<<"\t"<<"三个8带一个9："
           <<"\t"<<CardRule::getInstance()->canPickCard(pre,pid,cur,cid);
    return a.exec();
}
