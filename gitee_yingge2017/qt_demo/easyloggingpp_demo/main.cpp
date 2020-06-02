#include "mainwindow.h"
#include "easylogging++.h"

#include <QApplication>

INITIALIZE_EASYLOGGINGPP


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();


    el::Configurations conf("log.conf");
    el::Loggers::reconfigureAllLoggers(conf);

    LOG(ERROR)   << "-----error log";
    LOG(WARNING) << "-----warning log";
    LOG(INFO)    << "-----info log";

    LOG(TRACE)   << "-----trace log";
    LOG(DEBUG)   << "-----debug log";


    system("pause");


    return a.exec();
}
