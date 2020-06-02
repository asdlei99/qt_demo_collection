#ifndef ICONFACTORY_H
#define ICONFACTORY_H
#include <QPixmap>

class IconFactory
{
private:
    IconFactory();

public:
    static IconFactory* Instance(){
        static IconFactory T;
        return &T;
    }

    void createAll();

    QPixmap saveArrow();
    QPixmap saveArc();
    QPixmap saveZoomArrow();

    QPixmap savePoint();
    QPixmap saveLine();
    QPixmap saveFace();
};

#endif // ICONFACTORY_H
