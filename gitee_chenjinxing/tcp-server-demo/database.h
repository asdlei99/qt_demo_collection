#ifndef DATABASE_H
#define DATABASE_H
#include <stddef.h>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QObject>
#include <QList>
#include "user.h"
//单例模式的数据库操作类
class Database
{
private:
    Database();
    static Database * _db;
public:
    static Database * getInstance();

private:
    QSqlDatabase _sqldb;
};

#endif // DATABASE_H
