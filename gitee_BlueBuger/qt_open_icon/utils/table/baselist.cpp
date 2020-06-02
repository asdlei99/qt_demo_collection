/**
 ** @author:	   浓咖啡
 ** @date:	   2016.7.27
 ** @brief:      列表组件
 */

#include "baselist.h"

#define DEFAULT_LIST_STYLE "\
QTableWidget{\
    background:#FFFFFF;\
    selection-background-color:#EEEEE0;\
    font:bold;\
    color:#838B8B;\
    selection-color:#838B8B;\
    }\
    QScrollBar:vertical{\
    width:6px;\
    background-color: #ABABAB;\
    margin:0px,0px,0px,0px;\
    padding-top:0px; border-radius: 2px;\
    padding-bottom:0px;\
    }\
"

BaseList::BaseList()
{
    setStyleSheet(DEFAULT_LIST_STYLE);

    horizontalHeader()->setVisible(false);//设置水平方向表头
    verticalHeader()->setVisible(false);//设置垂直方向表头
    setSelectionBehavior(QAbstractItemView::SelectRows);  //设置行选择模式
    setSelectionMode(QAbstractItemView::SingleSelection);  //单选
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭水平滚动条
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); //设置垂直滚动条
    setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    setFrameShape(QFrame::NoFrame);  //无边框，无沉浸
    setShowGrid(false);//网格不显示
    setFocusPolicy(Qt::NoFocus);  //无焦点

    setItemDelegate(new LineDelegate(this));

    connect(this, SIGNAL(currentCellChanged(int,int,int,int)),\
            this, SLOT(currentCellChangedSlot(int,int,int,int)));
}

void BaseList::currentCellChangedSlot(int currentRow, int currentColumn, \
                                      int previousRow, int previousColumn)
{
    qDebug()<<"currentRow="<<currentRow<<" currentColumn="<<currentColumn;
    qDebug()<<"previousRow="<<previousRow<<" previousColumn="<<previousColumn;
}
