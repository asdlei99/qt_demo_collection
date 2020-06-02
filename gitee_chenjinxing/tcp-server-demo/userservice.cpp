#include "userservice.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

UserService::UserService()
{
}

UserService *UserService::Instance()
{
    static UserService T;
    return &T;
}
//新增用户 参数user保存新增后的结果 返回数据库收影响的行
int UserService::InsertUser(User &user)
{
    Database *db =Database::getInstance();
    QSqlQuery query;
    QString sql="select *from user where name ='"+user.getName()+"';";
    //执行sql语句
    query.exec(sql);
    while(query.next())
    {
        user.setId(-1);
        return 0;   //如果存在相同的用户，直接返回为0
    }
    //如果没有相同登录名的话，就插入
    sql="insert into user values(NULL,'"+user.getName()+"','"+user.getEmail()+"');";
    //执行sql语句
    if(query.exec(sql)){
        user.setId(getMaxUserId());
        return 1;
    }
    return 0;
}

bool UserService::modifyUser(const User &user)
{
    Database *db =Database::getInstance();
    QSqlQuery query;
    QString sql="update user set name='"+user.getName()+"',email='"+user.getEmail()+"' where id ='"+QString::number(user.getId())+"';";
    //执行sql语句
    return query.exec(sql);
}


QList<User> UserService::getAllUsers()
{
    QList<User> userList;
    Database *db =Database::getInstance();
    QSqlQuery query;
    QString sql="select *from user;";
    //执行sql语句
    query.exec(sql);
    while(query.next())
    {
        User user;
        user.setId(query.value(0).toInt());
        user.setName(query.value(1).toString());
        user.setEmail(query.value(2).toString());
        userList.append(user);
    }
    return userList;
}

bool UserService::deleteUser(int id)
{
    Database *db =Database::getInstance();
    QSqlQuery query;
    QString sql="delete from user where id ='"+QString::number(id)+"';";
    //执行sql语句
    return query.exec(sql);
}

User UserService::loadUser(int id)
{
    Database *db =Database::getInstance();
    QSqlQuery query;
    QString sql="select *from user where id='"+QString::number(id)+"'";
    query.prepare(sql);
    query.bindValue(":id",QVariant(id));
    //执行sql语句
    query.exec(sql);
    User user;
    user.setId(0);
    while(query.next())
    {
        user.setId(query.value(0).toInt());
        user.setName(query.value(1).toString());
        user.setEmail(query.value(2).toString());
    }
    return user;
}

int UserService::getMaxUserId()
{
    Database *db =Database::getInstance();
    QSqlQuery query;
    query.exec("select Max(id) from user");
    if(!query.next())
    {
        return 0;
    }
    return query.value(0).toInt();
}

