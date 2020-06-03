#ifndef CARDTABLE_H
#define CARDTABLE_H
#include <carddeck.h>
#include <QWidget>

class CardTable : public QWidget {
    public:
    CardTable();
    private:
    CardDeck m_deck;

};

#endif        //  #ifndef CARDTABLE_H
