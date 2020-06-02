/**
 ** @author:	   浓咖啡
 ** @date:	   2016.12.6
 ** @brief:      列表委托类，去掉左右边框显示
 */

#ifndef LINEDELEGATE_H
#define LINEDELEGATE_H

#include "platformhead.h"

class LineDelegate : public QStyledItemDelegate
{
public:
    LineDelegate(QTableView *tableView);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    QPen pen;
    QTableView *view;
    const int gridGap = 5;  //边框离边线距离
    int colNum;  //列数
};

#endif // LINEDELEGATE_H
