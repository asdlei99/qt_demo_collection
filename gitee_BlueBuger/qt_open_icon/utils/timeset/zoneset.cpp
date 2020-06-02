/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.30
 ** @brief:      时区界面
 */

#include "zoneset.h"

ZoneSet::ZoneSet(QWidget *parent) :
    QWidget(parent)
{
    //标题栏
    head = new HeadUtils("时区设置", this);
    //表格
    createZoneList();
    table = new ZoneTable(zonelist);

    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->addWidget(head);
    lay->addWidget(table);
    lay->setMargin(0);
    lay->setSpacing(0);

    connect(head, SIGNAL(backSignal()), this, SIGNAL(backDisp()));
    setFixedSize(355, 200);
    setStyleSheet("background-color:#FFFFFF;");
}

void ZoneSet::createZoneList()
{
    zonelist<<("北京\nGMT+8:00")<<("香港\nGMT+8:00")<<("首尔\nGMT+9:00")<<("悉尼\nGMT+10:00")<<("曼谷\nGMT+7:00");
}
