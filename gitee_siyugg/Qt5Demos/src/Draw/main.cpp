#include "DrawWindow.h"
#include "DrawArea.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawWindow w;
    //DrawArea w;
    w.show();

    return a.exec();
}
