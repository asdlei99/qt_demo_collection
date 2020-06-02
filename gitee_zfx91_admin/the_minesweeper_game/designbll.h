#ifndef DESIGNBLL_H
#define DESIGNBLL_H
#include <QObject>
#include <QQmlContext>
#include "DesignModel.h"//类必须继承与QObject


class DesignBLL :public QObject
{
    Q_OBJECT
public :
    DesignBLL(QObject* parent = nullptr);

    void init(int sizeW, int sizeH, int mineSize);

    QList<QObject*> getModel();


    bool ClickItem(const int index);

    QString GetPath(const int index);
private:

    void checkMine(QRect rect, QPoint pos);

private:
    QList<QObject*> m_data;//作用等同与ListModel


    int GameMap[25][25];

};
#endif // DESIGNBLL_H
