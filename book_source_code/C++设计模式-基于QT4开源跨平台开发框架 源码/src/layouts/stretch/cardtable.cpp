#include "cardtable.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

// Given a pixmap, return a label with that pixmap on it.
static QLabel* label(QPixmap pm) {
    QLabel* retval = new QLabel();
    retval->setPixmap(pm);
    return retval;
}

CardTable::CardTable() {

    QHBoxLayout *row = new QHBoxLayout();
    row->addWidget(label(m_deck.get(1)));  
    row->addWidget(label(m_deck.get(2)));
    row->addWidget(label(m_deck.get(3)));
    row->addWidget(label(m_deck.get(4)));    

    QVBoxLayout* rows = new QVBoxLayout();
    rows->addLayout(row);
    
    row = new QHBoxLayout();
    row->addWidget(label(m_deck.get(5)));
    row->addWidget(label(m_deck.get(6)));
    row->addWidget(label(m_deck.get(7)));
    rows->addLayout(row);
    //start
    QVBoxLayout *buttons = new QVBoxLayout();
    
    buttons->addStretch(1);     /* stretchable space before buttons in column */
    buttons->addWidget(new QPushButton("Deal"));
    buttons->addWidget(new QPushButton("Shuffle"));
    buttons->addSpacing(20);    /* fixed spacing after buttons */

    QHBoxLayout* cols = new QHBoxLayout();
    setLayout(cols);    
    cols->addLayout(rows);      
    cols->addStretch(30);       /* Adds a fixed spacing of 30 that stretches */
    cols->addLayout(buttons);   
}
//end
