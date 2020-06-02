#ifndef CCONTROL_H
#define CCONTROL_H

#include <QObject>

#include "designbll.h"

class CControl : public QObject
{
    Q_OBJECT
public:
    explicit CControl(QObject *parent = nullptr);

signals:

public slots:

    void init();

    //qml界面，组件点击指令
    Q_INVOKABLE bool clickItem(const int index);

    //将c++数据提供给qml
    Q_INVOKABLE QList<QObject*> getModel();//必须加上Q_INVOKABLE才可以在QML被调用

    //通过index获取item对应的图标
    Q_INVOKABLE QString getPath(const int index);


    Q_INVOKABLE int getRow() { return m_RowNum; }
    Q_INVOKABLE int getColumn() { return m_ColumnNum; }
private:
    DesignBLL *designBLL;


    int m_RowNum;
    int m_ColumnNum;
};

#endif // CCONTROL_H
