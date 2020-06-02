/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.30
 ** @brief:      时区界面需要的表格组件
 */

#include "zonetable.h"

#define QTABLEWIDGET_STYLE "\
QTableWidget{\
    background:#FFFFFF;\
    selection-background-color:#FFFFFF;\
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

#define LABEL_STYLE "\
QLabel{\
    color:#71C671;\
    font:15px;\
    border:0px;\
    background-color:rgb(0,0,0,0);\
}\
"

ZoneTable::ZoneTable(const QStringList &list):
    first(true)
{
    setRowCount(list.length());
    setColumnCount(columnCount);
    setFixedSize(355, 165);
    setColumnWidth(0, 40);
    setColumnWidth(1, 100);
    setColumnWidth(2, 175);
    setColumnWidth(3, 40);
    verticalHeader()->setDefaultSectionSize(50);
    setStyleSheet(QTABLEWIDGET_STYLE);

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

    for(int i=0; i<list.length(); i++){
        QTableWidgetItem *item = new QTableWidgetItem(list.at(i));
        setItem(i,1,item);
    }

    BaseLabel *label = new BaseLabel(FontawesomeWebfont(), \
                                    FontawesomeWebfont::ICON_CHECK, 30, 50, LABEL_STYLE);

    setCellWidget(0, columnCount-1, label);
    connect(this, SIGNAL(currentCellChanged(int,int,int,int)),\
            this, SLOT(currentCellChangedSlot(int,int,int,int)));
}

/**
 * @brief 改变选择行数后触发
 */
void ZoneTable::currentCellChangedSlot(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
        if(first){
            removeCellWidget(0, columnCount-1);
            first = false;
        }else{
            removeCellWidget(previousRow, columnCount-1);  //删除上一个，防止内存泄漏
        }

        BaseLabel *label = new BaseLabel(FontawesomeWebfont(), \
                                        FontawesomeWebfont::ICON_CHECK, 30, 50, LABEL_STYLE);
        setCellWidget(currentRow, columnCount-1, label);
}
