#ifndef QUERY_H
#define QUERY_H

#include <QObject>
#include <qdebug.h>
#include <qsqldatabase.h>
#include <qsqlerror.h>
#include <qsqlquery.h>
#include <QSqlRecord>

class SqliteQuery
{
public:
    ~SqliteQuery();
    static SqliteQuery *instance();
     void connect();
     void insert(QStringList &list);
     void fresh();
private:
     SqliteQuery();

private:
     QSqlDatabase database;
};

#endif // QUERY_H
