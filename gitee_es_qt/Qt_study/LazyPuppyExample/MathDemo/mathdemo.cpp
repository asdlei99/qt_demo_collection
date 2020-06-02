#include <QCoreApplication>
#include <QtMath>
#include <QtDebug>

static void arctanTest()
{
    for (int i=0; i<=180; i+=10) {
        float v = qDegreesToRadians(float(i));
        double fx =  qCos(v);
        double fy = qSin(v);
        double angle = qAtan2(fy, fx);
        qDebug("angle=%d,%f,%f fx=%f, fy=%f", i, v,angle, fx, fy);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    arctanTest();
    return a.exec();
}
