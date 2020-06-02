/**
 ** @author:	   浓咖啡
 ** @date:	   2016.7.27
 ** @brief:      普通列表组件
 */

#include "normallist.h"

NormalList::NormalList(const QStringList &list)
{
    setRowCount(list.length());
    setColumnCount(2);
    for(int i=0; i<list.length(); i++){
        QTableWidgetItem *item = new QTableWidgetItem(list.at(i));
        setItem(i,0,item);
    }
}
