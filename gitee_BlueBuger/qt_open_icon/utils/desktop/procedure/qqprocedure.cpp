/**
 ** @author:	   浓咖啡
 ** @date:	   2016.10.12
 ** @brief:      qq应用程序示例
 */
#include "qqprocedure.h"

QQProcedure::QQProcedure():Procedure("qq", "qqproce.exe")
{
//    setArgQWS();  //嵌入式qt程序需要增加选项
}

BaseButton *QQProcedure::createIcon()
{
    BaseButton *iconBtn = new BaseButton(MuiFont(), MuiFont::ICON_QQ, 100, 100);
    return iconBtn;
}
