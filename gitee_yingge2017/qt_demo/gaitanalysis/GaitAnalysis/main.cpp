#include "mainwindow.h"
#include "logindialog.h"
#include "connector.h"
#include "footwidget.h"

#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    cout<<"main"<<endl;

    //    MainWindow w;
    //    w.show();

    //    LoginDialog d;
    //    d.exec();

//    Connector c;

    FootWidget f;
    f.show();

    cout<<"main end"<<endl;

    return a.exec();
}
