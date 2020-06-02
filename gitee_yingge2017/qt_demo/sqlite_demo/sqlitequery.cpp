#include "sqlitequery.h"

#include <sstream>

using namespace std;

void SqliteQuery::connect()
{
    //添加数据库驱动、设置数据库名称、数据库登录用户名、密码
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("database.db");
    database.setUserName("root");
    database.setPassword("root");

    //打开数据库
    if(!database.open())
    {
        qDebug()<<"database open failed."<<database.lastError();
        return;
    }

    qDebug()<<"database open ok.";
    QSqlQuery qry;
    //创建表
    qry.prepare( "CREATE TABLE IF NOT EXISTS names (id INTEGER UNIQUE PRIMARY KEY, name VARCHAR(30), passwd VARCHAR(30),marks VARCHAR(99))" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug() << "Table created!";



}

void SqliteQuery::insert(QStringList &list)
{
    if(list.value(0).isNull() || list.value(0).isEmpty()){
        qDebug()<<"insert name is null";
        return;
    }

    QSqlQuery qry(database);
#if 1
    stringstream  ss;
    ss<<"INSERT into names(name,passwd,marks)VALUES('";
    ss<<list.value(0).toStdString()<<"','"
     <<list.value(1).toStdString()<<"','"
    <<list.value(2).toStdString()<<"');";
    //  插入数据
    //    qry.prepare( "INSERT into names(id,firstname,lastname)VALUES(4,'aaaa','sssss'),(5,'bbbb','dddd');");
    QString queryStr = QString::fromStdString(ss.str());
    qDebug()<<"insert queryStr:"<<queryStr;
    qry.prepare(queryStr);
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug( "Inserted!" );
#endif

}

void SqliteQuery::fresh()
{
    QSqlQuery qry;
    //查询数据
    qry.prepare( "SELECT * FROM names" );
    if( !qry.exec() )
        qDebug()<<"select failed." << qry.lastError();
    else
    {
        qDebug( "Selected!" );

        QSqlRecord record = qry.record();

        int columnCount = record.count();
        //列信息
        for( int c=0; c<columnCount; c++ ){
            qDebug() << QString( "Column %1: %2" ).arg( c ).arg( record.fieldName(c) );
        }

        for( int r=0; qry.next(); r++ ){
            for( int c=0; c<columnCount; c++ ){
                qDebug() << QString( "Row %1, %2: %3" ).
                            arg( r ). //行号
                            arg( record.fieldName(c) ). //行名称
                            arg( qry.value(c).toString() );//数据，通过列号来获取数据.
            }
        }
    }

}


SqliteQuery::~SqliteQuery()
{
database.close();
}

SqliteQuery *SqliteQuery::instance()
{
    static SqliteQuery ins ;
    return &ins;
}

SqliteQuery::SqliteQuery()
{
    connect();
}
