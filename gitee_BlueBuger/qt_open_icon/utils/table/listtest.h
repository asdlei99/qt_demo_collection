#ifndef LISTTEST_H
#define LISTTEST_H

#include "normallist.h"
#include "navlist.h"

class ListTest : public QWidget
{
    Q_OBJECT
public:
    explicit ListTest(QWidget *parent = 0);

signals:

public slots:

private:
    NormalList *normalList;
    NavList *navList;
};

#endif // LISTTEST_H
