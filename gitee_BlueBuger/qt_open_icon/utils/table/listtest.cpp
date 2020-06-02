#include "listtest.h"

ListTest::ListTest(QWidget *parent) :
    QWidget(parent)
{
    QStringList zonelist;
    zonelist<<("北京")<<("香港")<<("首尔");

    normalList  = new NormalList(zonelist);//普通列表
    navList = new NavList(zonelist, ":/images/resourse/images/list/forward.png");//带箭头的列表

    QVBoxLayout *lay = new QVBoxLayout(this);


    lay->addWidget(normalList);
    lay->addWidget(navList);
}
