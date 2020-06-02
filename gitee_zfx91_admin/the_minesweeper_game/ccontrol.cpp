#include "ccontrol.h"

CControl::CControl(QObject *parent) : QObject(parent)
{
    designBLL = new DesignBLL(this);

    m_RowNum = 25;
    m_ColumnNum = 25;

}

void CControl::init()
{
    int mine_size = 80;
    designBLL->init(m_RowNum, m_ColumnNum, mine_size);
}

bool CControl::clickItem(const int index)
{
    return designBLL->ClickItem(index);
}

QList<QObject *> CControl::getModel()
{
    return designBLL->getModel();
}

QString CControl::getPath(const int index)
{
    return designBLL->GetPath(index);
}
