#include "loopbutton.h"

LoopButton::LoopButton(const AbstractFont &fontLib, int iconIndex, int w, int h, const QString &style):
    BaseButton(fontLib, iconIndex, w, h, style),
    curIndex(0)
{
}

/**
 * @brief 切换到指定的图标
 * @param index
 */
void LoopButton::switchIndex(int index)
{
    if(index<iconList.length() && index>0){
        restoreFont();
        iconhelp::setIcon(this,index);
    }
}




