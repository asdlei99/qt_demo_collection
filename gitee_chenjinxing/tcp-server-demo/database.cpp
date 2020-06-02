#include "database.h"
#include <QSqlError>
#include <QDebug>
Database* Database::_db = NULL;
Database::Database()
{
    //构造函数的时候就去加载数据库驱动
    _sqldb =QSqlDatabase::addDatabase("QSQLITE");
    _sqldb.setDatabaseName("db");
    //打开数据库
    if(!_sqldb.open())
    {
        qDebug()<<_sqldb.lastError().text();
    }
    //初始化数据库表格
    QSqlQuery query;
    QString sql="create table if not exists user(\
            id integer primary key autoincrement,\
            name varchar(20),\
            email varchar(20)\
            );";
    query.exec(sql);
    if (!query.isActive())
        qDebug()<<"初始化数据库失败";
}

Database *Database::getInstance()
{
    if(_db == NULL)
    {
        _db =new Database();
    }
    return _db;
}
