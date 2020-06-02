#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 1
    MainWindow w;
    w.resize(1222,888);
    w.show();
#endif

    return a.exec();
}
