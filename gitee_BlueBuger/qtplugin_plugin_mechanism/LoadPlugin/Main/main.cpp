#include "loadplugin.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoadPlugin w;
    //w.show();
    return a.exec();
}
