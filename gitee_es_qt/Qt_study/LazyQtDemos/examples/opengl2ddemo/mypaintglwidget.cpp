#include "mypaintglwidget.h"

#include <QPainter>
#include "myhelp.h"

MyPaintGlWidget::MyPaintGlWidget(MyHelp *helper, QWidget *parent)
    : QOpenGLWidget (parent), helper(helper)
{
    setFixedSize(200, 200);
    setAutoFillBackground(false);
}

void MyPaintGlWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;

    painter.begin(this);
    helper->paint(&painter, event, 0);

    painter.end();
}
