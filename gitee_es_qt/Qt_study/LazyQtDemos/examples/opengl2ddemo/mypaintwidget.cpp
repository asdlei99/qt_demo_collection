#include "mypaintwidget.h"

#include <QPainter>

#include "myhelp.h"


MyPaintWidget::MyPaintWidget(MyHelp *helper, QWidget *parent)
    :QWidget (parent), helper(helper)
{
    setFixedSize(200, 200);
}

void MyPaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event, 0);
    painter.end();
}
