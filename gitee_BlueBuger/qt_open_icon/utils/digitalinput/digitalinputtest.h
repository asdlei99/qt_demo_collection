#ifndef DIGITALINPUTTEST_H
#define DIGITALINPUTTEST_H

#include "digitalinput.h"

class DigitalInputTest : public QWidget
{
    Q_OBJECT
public:
    explicit DigitalInputTest(QWidget *parent = 0);

signals:

public slots:

private:
    DigitalInput *digWig;
};

#endif // DIGITALINPUTTEST_H
