/**
 ** @author:	   浓咖啡
 ** @date:	   2016.7.28
 ** @brief:      带导航列表组件
 */

#ifndef NAVLIST_H
#define NAVLIST_H

#include "baselist.h"

class NavList : public BaseList
{
    Q_OBJECT
public:
    NavList(const QStringList &list, const QString &pixPath);
};
#endif // NAVLIST_H
