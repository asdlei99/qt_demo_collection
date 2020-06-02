#include "switchbutton.h"

/**
 * @brief SwitchButton::SwitchButton
 * @param fontLib 需要的字体库
 * @param iconIndex1 转换图标1索引（默认）
 * @param iconIndex2 转换图标2索引
 * @param w 长
 * @param h 宽
 * @param style 样式
 */
SwitchButton::SwitchButton(const AbstractFont &fontLib, int iconIndex1, int iconIndex2, int w, int h, const QString &style):
    BaseButton(fontLib, iconIndex1, w, h, style),
    flag(true)
{
    index1 = iconIndex1;
    index2 = iconIndex2;
}


void SwitchButton::releaseSlot()
{
    restoreFont();
    if(flag){
        iconhelp::setIcon(this,index2);
        flag = false;
    }else{
        iconhelp::setIcon(this,index1);
        flag = true;
    }
}
