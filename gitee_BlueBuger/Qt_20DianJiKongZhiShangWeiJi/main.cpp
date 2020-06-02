#include "mainwindow.h"
#include <QApplication>
#include <QByteArray>
#include "math.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    setbuf(stdout,NULL);
    setbuf(stderr,NULL);
    MainWindow w;
    w.show();

    return a.exec();
}

