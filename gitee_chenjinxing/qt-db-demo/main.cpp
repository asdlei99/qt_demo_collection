#include "dbwgt.h"
#include <QApplication>
#include "database.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Database::getInstance();
    DbWgt w;
    w.show();

    return a.exec();
}
