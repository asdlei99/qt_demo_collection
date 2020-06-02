#include "pokershowwgt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PokerShowWgt w;
    w.show();

    return a.exec();
}
