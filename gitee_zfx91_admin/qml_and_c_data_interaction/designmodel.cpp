#include "DesignModel.h"

DesignModel::DesignModel(const QString &backColor,QObject *parent):QObject(parent),
    m_backColor(backColor)
{

}

QString DesignModel::backColor() const
{
    return m_backColor;
}

void DesignModel::setBackColor(const QString &backColor)
{
    m_backColor=backColor;
    emit backColorChanged();
}
