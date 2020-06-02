#include "qsoundwgt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSoundWgt w;
    w.show();

    return a.exec();
}
