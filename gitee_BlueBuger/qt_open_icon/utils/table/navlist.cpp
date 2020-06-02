/**
 ** @author:	   浓咖啡
 ** @date:	   2016.7.28
 ** @brief:      带导航列表组件
 */

#include "navlist.h"

NavList::NavList(const QStringList &list, const QString &pixPath)
{
    setRowCount(list.length());
    setColumnCount(2);
    for(int i=0; i<list.length(); i++){
        QTableWidgetItem *item = new QTableWidgetItem(list.at(i));
        setItem(i,0,item);
        item = new QTableWidgetItem;
        item->setIcon(QIcon(QPixmap(":/images/resourse/images/list/forward.png")));
        setItem(i,1,item);
    }
}

