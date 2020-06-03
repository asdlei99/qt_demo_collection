#include "sliderlcd.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char ** argv) {
    QApplication app(argc, argv);    
    SliderLCD slcd;
    slcd.show();
    qDebug() << QString("This is a debug message.");
    return app.exec();
}

