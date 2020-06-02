#ifndef DIGITALINPUT_H
#define DIGITALINPUT_H

#include "basebutton.h"

class DigitalInput : public QWidget
{
    Q_OBJECT
public:
    explicit DigitalInput(int w, int h);
    void initVal(int val);

signals:

private slots:
    void addSlot();
    void downSlot();

private:
    BaseButton *add;
    BaseButton *down;
    QLineEdit *textEdit;
    int curNum;
};

#endif // DIGITALINPUT_H
