#include "cardtable.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

//start
// Given a pixmap, return a label with that pixmap on it.
static QLabel* label(QPixmap pm) {
    QLabel* retval = new QLabel();
    retval->setPixmap(pm);
    return retval;
}

CardTable::CardTable() {

    // create 2 rows of cards:
    QHBoxLayout *row = new QHBoxLayout();
    row->addWidget(label(m_pixmaps.get("ah")));  
    row->addWidget(label(m_pixmaps.get("qd")));
    row->addWidget(label(m_pixmaps.get("ks")));
    row->addWidget(label(m_pixmaps.get("8c")));    

    QVBoxLayout* rows = new QVBoxLayout();
    rows->addLayout(row);
    
    row = new QHBoxLayout();
    row->addWidget(label(m_pixmaps.get("qs")));
    row->addWidget(label(m_pixmaps.get("js")));
    row->addWidget(label(m_pixmaps.get("td")));
    rows->addLayout(row);

    // create a column of buttons:
    QVBoxLayout *buttons = new QVBoxLayout();
    buttons->addWidget(new QPushButton("Deal"));
    buttons->addWidget(new QPushButton("Shuffle"));

    // Bring them together:
    QHBoxLayout* cols = new QHBoxLayout();
    setLayout(cols);           /* The "root layout" for this widget */
    cols->addLayout(rows);     /* Add both card rows as a column */
    cols->addLayout(buttons);  /* Add column of buttons as another column */
}
//end
