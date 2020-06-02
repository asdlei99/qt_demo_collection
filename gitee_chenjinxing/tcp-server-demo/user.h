#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();


private:
    int id;         //用户ID
    QString name;   //用户名
    QString email;  //邮箱

public:

    int getId() const;
    void setId(int value);

    QString getName() const;
    void setName(const QString &value);

    QString getEmail() const;
    void setEmail(const QString &value);
};

#endif // USER_H
