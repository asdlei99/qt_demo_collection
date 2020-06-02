#include "qt_serial.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qt_serial w;
    w.show();

    return a.exec();
}
