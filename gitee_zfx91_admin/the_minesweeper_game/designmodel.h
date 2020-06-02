#ifndef DESIGNMODEL_H
#define DESIGNMODEL_H


#include <QObject>
#include <QPoint>
#include "cenum.h"


class DesignModel:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString backColor READ backColor WRITE setBackColor NOTIFY backColorChanged)
public:
    DesignModel(QObject *parent = 0);

    //以二维数据形式，标记每个item的位置信息
    inline void SetPos(const int row, const int column) {
        m_row = row;
        m_column = column;
    }
    inline QPoint GetPos() {
        return QPoint(m_row, m_column);
    }

    //设置item的状态
    inline void SetItemType(CEnum::CItemType type)  { m_type = type; }
    inline CEnum::CItemType GetItemType()   { return m_type; }

    //记录item周边有几个雷
    inline void SetMineNum(const int num) { m_MineNum = num; }
    inline int GetMineNum() {return m_MineNum; }


    QString backColor() const;
    void setBackColor(const QString &backColor);

signals:
    void backColorChanged();

private:
    QString m_backColor;

    int  m_row, m_column;      //组件的id
    CEnum::CItemType m_type;

    int m_MineNum = 0;
};
#endif // DESIGNMODEL_H
