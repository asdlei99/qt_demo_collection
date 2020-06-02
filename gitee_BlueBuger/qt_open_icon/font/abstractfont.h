#ifndef ABSTRACTFONT_H
#define ABSTRACTFONT_H

#include "platformhead.h"

/**
 * @brief 抽象字体库基类
 */
class AbstractFont
{
public:
    explicit AbstractFont(const QString &_name);
    QFont getIconFont()const{return iconFont;}
    QString getIconName()const{return name;}

private:
    QFont iconFont;
    QString name; //字体库的名称  比如：mui/fontawesome-webfont
};

#endif // ABSTRACTFONT_H
