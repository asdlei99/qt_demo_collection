#include "containwidget.h"

#include <QGridLayout>
#include <QLabel>

#include "mypaintwidget.h"
#include "mypaintglwidget.h"

ContainWidget::ContainWidget(QWidget *parent) : QWidget(parent)
{

    setWindowTitle(tr("演示2d画图"));
    // 加入两个窗口
    MyPaintWidget *native = new MyPaintWidget(&helper, this);
    QLabel *nativeLabel = new QLabel(tr("Native"));

    MyPaintGlWidget *glWidget = new MyPaintGlWidget(&helper, this);
    QLabel *glLabel = new QLabel(tr("OpenGL"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(native, 0, 0);
    layout->addWidget(nativeLabel, 1, 0);
    layout->addWidget(glWidget, 0, 1);
    layout->addWidget(glLabel, 1, 1);

    setLayout(layout);

}
