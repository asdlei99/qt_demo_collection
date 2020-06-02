#include "digitalinput.h"

#define LEFT_STYLE "\
QPushButton{\
color:#000000;\
font:50px;\
border:1px solid #AAAAAA;\
    border-top-left-radius:5;\
    border-bottom-left-radius:5;\
    background-color:#FFFFFF;\
}\
QPushButton:pressed{\
color:#FFFFFF;\
    background-color:#AAAAAA;\
}\
"

#define RIGHT_STYLE "\
QPushButton{\
color:#000000;\
font:50px;\
border:1px solid #AAAAAA;\
    border-top-right-radius:5;\
    border-bottom-right-radius:5;\
    background-color:#FFFFFF;\
}\
QPushButton:pressed{\
color:#FFFFFF;\
    background-color:#AAAAAA;\
}\
"


#define EDIT_STYLE "\
QLineEdit{\
    border-top-width:1px;\
    border-bottom-width:1px;\
    border-color:#AAAAAA;\
    background-color:#FFFFFF;\
    font: 43px;\
}\
QLineEdit:focus {\
    border-top-width:1px;\
    border-bottom-width:1px;\
    border-color:#AAAAAA;\
    background-color:#FFFFFF;\
    font: 43px;\
}\
"


DigitalInput::DigitalInput(int w, int h)
{
    curNum = 0;

    add = new BaseButton(MuiFont(), MuiFont::ICON_PLUS, w, h, LEFT_STYLE);
    down = new BaseButton(MuiFont(), MuiFont::ICON_MINUS, w, h, RIGHT_STYLE);
    textEdit = new QLineEdit();
    textEdit->setMinimumSize(50, 52);
    textEdit->setStyleSheet(EDIT_STYLE);
    textEdit->setText(QString::number(curNum, 10));

    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setSpacing(0);
    lay->setMargin(0);
    lay->addWidget(down);
    lay->addWidget(textEdit);
    lay->addWidget(add);

    connect(add,SIGNAL(btnReleased()),this,SLOT(addSlot()));
    connect(down,SIGNAL(btnReleased()),this,SLOT(downSlot()));
}

void DigitalInput::initVal(int val)
{
    curNum = val;
    textEdit->setText(QString::number(curNum, 10));
}

void DigitalInput::addSlot()
{
    curNum++;
    textEdit->setText(QString::number(curNum, 10));
}

void DigitalInput::downSlot()
{
    curNum--;
    textEdit->setText(QString::number(curNum, 10));
}
