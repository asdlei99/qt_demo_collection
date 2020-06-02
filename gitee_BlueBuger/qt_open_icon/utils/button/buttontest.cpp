#include "buttontest.h"

//渐变样式示例
#define SWITCH_BUTTON_STYLE "\
QPushButton{\
    color:QLinearGradient(x1:0, y1:0, x2:0, y2:1,stop:0 #CC00CC, stop:1 #CCFF99);\
    border:1px solid #AAAAAA;\
    font:100px;\
    border-radius:5;\
    background: QLinearGradient(x1:0, y1:0, x2:0, y2:1,stop:0 #0066FF, stop:1 #33FFFF);\
}\
QPushButton:pressed{\
    color:QLinearGradient(x1:0, y1:0, x2:0, y2:1,stop:0 #CCEEFF, stop:1 #F0BBFF);\
    background: QLinearGradient(x1:0, y1:0, x2:0, y2:1,stop:0 #FF8800, stop:1 #FFFF77);\
}\
"

#define DEFULT_LABEL_STYLE "\
QLabel{\
    color:#000000;\
    font:40px;\
    border:0px;\
    background-color:rgb(0,0,0,0);\
}\
"


ButtonTest::ButtonTest(QWidget *parent) :
    QWidget(parent)
{
    //BaseButton
    QLabel *baseButtonLab = new QLabel("BaseButton:");
    BaseButton *baseButton = new BaseButton(MuiFont(), MuiFont::ICON_WEINXIN, 200, 100);

    //batteryButtonLab
    QLabel *batteryButtonLab = new QLabel("BatteryButton:");
    BatteryButton *batteryButton = new BatteryButton(BatteryButton::EMPTY, EMPTY_BATTERY_STYLE);

    //switchbutton
    QLabel *switchButtonLab = new QLabel("SwitchButton:");
    SwitchButton *switchButton = new SwitchButton(FontawesomeWebfont(), \
                                                  FontawesomeWebfont::ICON_UNLOCK,
                                                  FontawesomeWebfont::ICON_LOCK,
                                                  200, 100, SWITCH_BUTTON_STYLE);

    //groupbutton
    QLabel *gourpButtonLab = new QLabel("GourpButton:");
    GroupButton *groupButton = new GroupButton(MuiFont(), \
                                                  MuiFont::ICON_WEINXIN,
                                               200, 100, "微信", "", "");

    lay = new QGridLayout(this);
    lay->addWidget(baseButtonLab, 0, 0);
    lay->addWidget(baseButton, 0, 1);
    lay->addWidget(batteryButtonLab, 0, 2);
    lay->addWidget(batteryButton, 0, 3);
    lay->addWidget(switchButtonLab, 1, 0);
    lay->addWidget(switchButton, 1, 1);
    lay->addWidget(gourpButtonLab, 1, 2);
    lay->addWidget(groupButton, 1, 3);
}
