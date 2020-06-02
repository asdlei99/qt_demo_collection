#ifndef DESIGNMODEL_H
#define DESIGNMODEL_H
#include<QObject>
#include<QVariant>
class DesignModel:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString backColor READ backColor WRITE setBackColor NOTIFY backColorChanged)
public:
    DesignModel(const QString &backColor,QObject *parent = 0);
    QString backColor() const;
    void setBackColor(const QString &backColor);
signals:
    void backColorChanged();
private:
    QString m_backColor;
};
#endif // DESIGNMODEL_H
