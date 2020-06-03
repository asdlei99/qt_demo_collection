#ifndef CARDTABLE_H
#define CARDTABLE_H
#include <cardpics.h>
#include <QWidget>

class CardTable : public QWidget {
  public:
    CardTable();
  private:
    CardPics m_pixmaps;

};

#endif        //  #ifndef CARDTABLE_H
