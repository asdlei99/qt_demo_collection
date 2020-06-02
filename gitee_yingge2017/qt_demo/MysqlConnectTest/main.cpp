#include <QCoreApplication>

#include "odbcconnector.h"

#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ODBCConnector localODBC;

    return a.exec();
}
