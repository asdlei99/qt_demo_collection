#ifndef BUTTONTEST_H
#define BUTTONTEST_H

#include "basebutton.h"
#include "switchbutton.h"
#include "batterybutton.h"
#include "groupbutton.h"

class ButtonTest : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonTest(QWidget *parent = 0);

signals:

private slots:

private:
    QGridLayout *lay;
};

#endif // BUTTONTEST_H
