#include "user.h"

User::User()
{

}

int User::getId() const
{
    return id;
}

void User::setId(int value)
{
    id = value;
}

QString User::getName() const
{
    return name;
}

void User::setName(const QString &value)
{
    name = value;
}

QString User::getEmail() const
{
    return email;
}

void User::setEmail(const QString &value)
{
    email = value;
}
