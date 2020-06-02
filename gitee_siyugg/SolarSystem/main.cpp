#include "SolorSystemWin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SolorSystemWin w;
    w.showMaximized();
    return a.exec();
}
