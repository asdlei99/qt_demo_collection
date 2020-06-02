#include "myglwindow.h"
#include "mygl2dwidget.h"
#include "containwidget.h"
#include <QApplication>

#define DEMO_NUM 2

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



#if DEMO_NUM == 1
    MyGLWindow w;
#elif DEMO_NUM == 2
    ContainWidget w;
#endif

    w.show();

    return a.exec();
}
