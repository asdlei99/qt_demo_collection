#ifndef USERSEIVICE_H
#define USERSEIVICE_H
#include "user.h"
#include "database.h"
#include <QList>
#include <QVector>
class UserService
{
private:
    UserService();

public:
    static UserService *Instance();
public:
    int InsertUser(User &user);      //新增用户 参数user保存新增后的结果 返回数据库收影响的行
    QList<User> getAllUsers();      //查找所有用户
    bool modifyUser(const User& user);     //修改用户
    bool deleteUser(int id);        //注销用户
    User loadUser(int id);          //加载用户


    int getMaxUserId();
};

#endif // USERSEIVICE_H
