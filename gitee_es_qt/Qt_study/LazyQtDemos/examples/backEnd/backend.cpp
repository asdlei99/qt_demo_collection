#include "backend.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{

}

QString BackEnd::userName()
{
    return m_userName;
}

void BackEnd::setUserName(const QString &userName)
{
    if (m_userName == userName) {
        return;
    }

    m_userName = userName;
    emit userNameChanged();
}
