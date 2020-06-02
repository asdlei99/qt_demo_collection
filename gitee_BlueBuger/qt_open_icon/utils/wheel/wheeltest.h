#ifndef WHEELTEST_H
#define WHEELTEST_H

#include "stringwheelwidget.h"
class WheelTest : public QWidget
{
    Q_OBJECT
public:
    explicit WheelTest(bool touch);

signals:

public slots:

private:
    StringWheelWidget *stringWheelWidget;
};

#endif // WHEELTEST_H
