#include "iconhelper.h"

IconHelper *IconHelper::_instance=0;

IconHelper::IconHelper()
{
    //默认用mui图标
    iconFont = MuiFont().getIconFont();
}

void IconHelper::setNewIcon(const AbstractFont &newFont)
{
    iconFont = newFont.getIconFont();
}
