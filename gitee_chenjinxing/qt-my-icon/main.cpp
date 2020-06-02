#include <QApplication>
#include "widget.h"
#include "iconfactory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IconFactory::Instance()->createAll();

    Widget w;
    w.show();

    return a.exec();
}
