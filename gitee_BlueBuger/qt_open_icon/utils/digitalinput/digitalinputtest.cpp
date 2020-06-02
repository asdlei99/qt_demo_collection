#include "digitalinputtest.h"

DigitalInputTest::DigitalInputTest(QWidget *parent) :
    QWidget(parent)
{
    digWig  = new DigitalInput(50, 50);
    QHBoxLayout *lay = new QHBoxLayout(this);

    lay->addWidget(digWig);
}
