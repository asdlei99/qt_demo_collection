#include "Qt5DemosDlg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Qt5DemosDlg dlg;
    dlg.show();

    return a.exec();
}
