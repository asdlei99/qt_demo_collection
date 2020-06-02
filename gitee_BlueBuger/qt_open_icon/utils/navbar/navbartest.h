#ifndef NAVBARTEST_H
#define NAVBARTEST_H

#include "navbar.h"

class NavBarTest : public QWidget
{
    Q_OBJECT
public:
    explicit NavBarTest(QWidget *parent = 0);

signals:

public slots:
    void lReleased();
    void rReleased();
};

#endif // NAVBARTEST_H
