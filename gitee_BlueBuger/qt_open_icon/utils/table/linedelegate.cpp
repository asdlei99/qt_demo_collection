#include "linedelegate.h"

LineDelegate::LineDelegate(QTableView *tableView)
{
    //首先拿到表格原来颜色
    int gridHint = tableView->style()->styleHint\
            (QStyle::SH_Table_GridLineColor, new QStyleOptionViewItemV4());
    QColor gridColor = static_cast<QRgb>(gridHint);
    pen = QPen(gridColor, 0, tableView->gridStyle());

    view = tableView;
    colNum = static_cast<QTableWidget *>(view)->columnCount();
}

void LineDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, \
                         const QModelIndex &index) const
{
    int curCol = index.column();
    QStyledItemDelegate::paint(painter, option, index);
    QPen oldPen = painter->pen();
    painter->setPen(pen);

    if(curCol == 0){  //第0列
        painter->drawLine(option.rect.bottomLeft().x() + gridGap, option.rect.bottomLeft().y(),
                          option.rect.bottomRight().x(), option.rect.bottomRight().y());
    }else if (curCol == colNum-1) {  //最后一列
        painter->drawLine(option.rect.bottomLeft().x(), option.rect.bottomLeft().y(),
                          option.rect.bottomRight().x()-gridGap, option.rect.bottomRight().y());
    }else {
        painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    }

    painter->setPen(oldPen);
}
