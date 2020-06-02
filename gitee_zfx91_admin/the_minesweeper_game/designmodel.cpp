#include "DesignModel.h"

DesignModel::DesignModel(QObject *parent):QObject(parent)
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
