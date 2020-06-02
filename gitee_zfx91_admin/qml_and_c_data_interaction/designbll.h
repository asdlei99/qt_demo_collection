#ifndef DESIGNBLL_H
#define DESIGNBLL_H
#include <QObject>
#include <QQmlContext>
#include "DesignModel.h"//类必须继承与QObject
class DesignBLL :public QObject
{
    Q_OBJECT
public :
    DesignBLL();
    Q_INVOKABLE QList<QObject*> getModel();//必须加上Q_INVOKABLE才可以在QML被调用
private:
    QList<QObject*> data;//作用等同与ListModel
};
#endif // DESIGNBLL_H
