#include "Utils.h"

#include <QCoreApplication>
#include <QTime>

Utils::Utils()
{

}

static QTime delayTime;
void Utils::delay(unsigned long msec)
{
    delayTime.start();
    while(delayTime.elapsed() < msec)
    {
        QCoreApplication::processEvents();
    }
}
