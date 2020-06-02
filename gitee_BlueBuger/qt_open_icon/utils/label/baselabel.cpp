/**
 ** @author:	   浓咖啡
 ** @date:	   2016.5.23
 ** @brief:      图标基类
 */
#include "baselabel.h"

#define DEFULT_LABEL_STYLE "\
QLabel{\
    color:#000000;\
    font:100px;\
    border:1px solid #AAAAAA;\
    background-color:rgb(255,255,255);\
}\
"

/**
 * @brief label基类
 * @param fontLib 选择字体库
 * @param iconIndex 选择字体库图标索引
 * @param w 长
 * @param h 宽
 * @param style 样式
 */
BaseLabel::BaseLabel(const AbstractFont &fontLib, int iconIndex, \
                     int w, int h, const QString &style)
{
    fontName = fontLib.getIconName();
    IconHelper::Instance()->setNewIcon(fontLib);
    iconhelp::setIcon(this,iconIndex);
    setFixedSize(w, h);
    if(style != QString()){
        setStyleSheet(style);
    }else{
        //如果用户提供按钮大小不足以装下字体大小，那么提示一下就好
        if(std::min(w, h) < 100){
//            qDebug()<<"default font is bigger than button";
        }
        setStyleSheet(DEFULT_LABEL_STYLE);
    }
}

/**
 * @brief BaseLabel::setNewIcon
 * @param iconIndex 新字体库图标索引
 * @param style 新样式
 */
void BaseLabel::setNewIcon(int iconIndex,const QString &style)
{
    //恢复字体库，防止别的组件更改字体库
    IconHelper::Instance()->setNewIcon(AbstractFont(fontName));
    iconhelp::setIcon(this,iconIndex);
    if(style != QString()){
        setStyleSheet(style);
    }
}
