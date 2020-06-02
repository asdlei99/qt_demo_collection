#ifndef TIMEFONT_H
#define TIMEFONT_H

#include "abstractfont.h"

class TimeFont : public AbstractFont
{
public:
    //随用随加
    enum ICON_INDEX{
        ICON_BACK = 0xe600,
        ICON_DATE = 0xe601,
    };
    explicit TimeFont();
};


#endif // TIMEFONT_H
