/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.8
 ** @brief:      电量显示按钮
 */

#ifndef BATTERYBUTTON_H
#define BATTERYBUTTON_H

#include "basebutton.h"

#define EMPTY_BATTERY_STYLE "\
QPushButton{\
    color:#FF0000 ;\
    font:100px;\
    border:0px;\
    border-radius:0;\
    background-color:#CCDDFF;\
}\
"

#define HALF_BATTERY_STYLE "\
QPushButton{\
    color:#FF8800 ;\
    font:100px;\
    border:0px;\
    border-radius:5;\
    background-color:#CCDDFF;\
}\
"

#define THREE_QUARTER_BATTERY_STYLE "\
QPushButton{\
    color:#88AA00 ;\
    font:100px;\
    border:0px;\
    border-radius:5;\
    background-color:#CCDDFF;\
}\
"

#define FULL_BATTERY_STYLE "\
QPushButton{\
    color:#00FF00 ;\
    font:100px;\
    border:0px;\
    border-radius:5;\
    background-color:#CCDDFF;\
}\
"

class BatteryButton : public BaseButton
{
public:
    enum POWER{
        EMPTY = FontawesomeWebfont::BATTERY_0,
        QUARTER = FontawesomeWebfont::BATTERY_1, // 1/4
        HALF = FontawesomeWebfont::BATTERY_2,
        THREE_QUARTER = FontawesomeWebfont::BATTERY_3,  // 3/4
        FULL = FontawesomeWebfont::BATTERY_4
    };

    BatteryButton(POWER power, const QString curStateStyle);
    void changePower(POWER power);

private:
    virtual void releaseSlot();
    int curIndex;
};

#endif // BATTERYBUTTON_H
