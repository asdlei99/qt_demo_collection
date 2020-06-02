#include "roomlistwgt.h"
#include <QApplication>
#include <roomwgt.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RoomListWgt w;
    //RoomWgt w;
    w.show();

    return a.exec();
}
