#include <QAction>
#include <QToolBar>
#include <QIcon>
#include <QToolButton>
#include <QGridLayout>
#include "widget.h"
#include "iconfactory.h"
#include "selectcontainer.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout * layout =new QGridLayout(this);

    QToolBar *toolBar =new QToolBar(this);

    SelectContainer *shapeChange =new SelectContainer(parent,true);
    toolBar->addWidget(addToolButtonByAction(shapeChange,IconFactory::Instance()->saveArc(),1));
    toolBar->addWidget(addToolButtonByAction(shapeChange,IconFactory::Instance()->saveArrow(),2));
    toolBar->addWidget(addToolButtonByAction(shapeChange,IconFactory::Instance()->saveZoomArrow(),3));
    toolBar->addSeparator();
    SelectContainer *editChange =new SelectContainer(parent);
    toolBar->addWidget(addToolButtonByAction(editChange,IconFactory::Instance()->savePoint(),1));
    toolBar->addWidget(addToolButtonByAction(editChange,IconFactory::Instance()->saveLine(),2));
    toolBar->addWidget(addToolButtonByAction(editChange,IconFactory::Instance()->saveFace(),3));

    layout->addWidget(toolBar);
}

Widget::~Widget()
{

}

QToolButton *Widget::addToolButton(const QPixmap &pixmap)
{
    QToolButton *btn =new QToolButton(this);
    btn->setIcon(QIcon(pixmap));
    btn->setFixedSize(30,30);

    return btn;
}

QToolButton *Widget::addToolButtonByAction(SelectContainer *container,const QPixmap &pixmap, const QVariant &data)
{
    QAction *action =new QAction(this);
    action->setData(data);
    action->setIcon(QIcon(pixmap));
    action->setCheckable(true);
    container->addAction(action);

    QToolButton *btn =new QToolButton(this);
    btn->setDefaultAction(action);
    btn->setFixedSize(30,30);
    return btn;
}
