#include "udp_server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    udp_server w;
    w.show();

    return a.exec();
}
