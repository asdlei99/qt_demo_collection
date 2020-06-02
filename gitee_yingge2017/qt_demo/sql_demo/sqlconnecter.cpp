#include "sqlconnecter.h"
#include <qsqlquery.h>
#include <qdebug.h>
#include <qsqlerror.h>
#include <qsqlrecord.h>
#include <qsqlquery.h>
#include <qsqlresult.h>
#include <qsqlrecord.h>
#include <qtextstream.h>
#include <qsqlfield.h>
#include <qsqldriver.h>
#include <QTableView>
#include <QSqlTableModel>

SqlConnecter::SqlConnecter(QObject *parent) : QObject(parent),
    m_db(QSqlDatabase::addDatabase("QMYSQL"))
{
    //    QString host = "192.168.110.126";
    //    QString dbName = "elsp";
    //    QString userName = "edq";
    //    QString pwd = "aaaaaa";

    QString host = "db4free.net";
    QString dbName = "zhongxingbidb";
    QString userName = "zhongxingbi";
    QString pwd = "zhongxingbi";

    m_db.setHostName(host);
    m_db.setPort(3306);
    m_db.setDatabaseName(dbName);
    m_db.setUserName(userName);
    m_db.setPassword(pwd);
    if(false == m_db.open()){
        qDebug()<<"database open failed."<<m_db.lastError().text();
        return;
    }else {
        qDebug()<<"database open ok.";
    }

    qDebug()<<"tables:"<<m_db.tables();

    //    selectAll("lf_adip");
    //    getColumnNames("lf_bbs_reply");
    //    descTable("lf_bbs_reply");

    //    insertTable();
    //    transactionFunc();
    //    insertTableList();

    tableViewFunc();

}

SqlConnecter::~SqlConnecter()
{
    m_db.close();
}

#if 0
void SqlConnecter::selectTable(const QString tableName)
{
    QSqlQuery query;
    //查询数据
    QString queryStr = "SELECT * FROM " + tableName;
     query.prepare(queryStr);
     if( !query.exec() )
         qDebug()<<"select failed." << query.lastError();
     else
     {
         qDebug( "Selected!" );

         QSqlRecord record = query.record();

         int columnCount = record.count();
         //列信息
         for( int c=0; c<columnCount; c++ ){
             qDebug() << QString( "Column %1: %2" ).arg( c ).arg( record.fieldName(c) );
         }

         for( int r=0; query.next(); r++ ){
             for( int c=0; c<columnCount; c++ ){
                 qDebug() << QString( "Row %1, %2: %3" ).
                             arg( r ).                          //行号
                             arg( record.fieldName(c) ).        //行名称
                             arg( query.value(c).toString() );  //数据
             }
         }
     }
#endif
void SqlConnecter::selectAll(const QString tableName)
{
    QSqlQuery query;

    QString queryStr = "select * from " + tableName + ";";
    //查询数据
    query.prepare(queryStr);
    if( !query.exec() )
        qDebug()<<"select failed." << query.lastError();
    else
    {
        qDebug( "Selected!" );
        //QSqlRecord封装了一条数据库记录
        QSqlRecord record = query.record();

        int columnCount = record.count();
        //列信息
        for( int c=0; c<columnCount; c++ ){
            qDebug() << QString( "Column %1: %2" ).arg( c ).arg( record.fieldName(c) );
        }

        for( int r=0; query.next(); r++ ){
            qDebug();
            for( int c=0; c<columnCount; c++ ){
                qDebug() << QString( "Row %1, %2: %3" ).
                            arg( r ). //行号
                            arg( record.fieldName(c) ). //行名称
                            arg( query.value(c).toString() );//数据
            }
        }
    }
}

void SqlConnecter::getColumnNames(const QString tableName)
{
    QSqlQuery query;

    QString queryStr = "select * from " + tableName + ";";
    //查询数据
    query.prepare(queryStr);
    if( !query.exec() )
        qDebug()<<"select failed." << query.lastError();
    else
    {
        qDebug( "Selected!" );
        //QSqlRecord封装了一条数据库记录
        QSqlRecord record = query.record();
        //记录有多少列
        int columnCount = record.count();
        //列信息
        for( int c=0; c<columnCount; c++ ){
            qDebug() << QString( "Column %1: %2" ).
                        arg( c ).arg( record.fieldName(c) );
        }
    }
}

void SqlConnecter::descTable(const QString tableName)
{
    QString queryStr = "desc " + tableName + ";";
    QSqlQuery query(queryStr);
    if(false == query.exec()){
        qDebug()<<"descTable query failed:"<<query.lastError();
        return;
    }

    while (query.next()) {
        qDebug()<<"new record.";
        //获取一条记录
        QSqlRecord sr = query.record();
        for(int i = 0;i<query.record().count();i++){
            //字段
            QSqlField sf = sr.field(i);
            qDebug()<<"sqlfiled:"<<sf.name()<<"|"<<sf.value();
        }
    }

}

void SqlConnecter::insertTable()
{
    //    lf_bbs_reply
    //    "Column 0: id"
    //    "Column 1: pid"
    //    "Column 2: uid"
    //    "Column 3: title"
    //    "Column 4: content"
    //    "Column 5: time"


    QString queryStr = "insert into `lf_bbs_reply`(pid,uid,title)values(?,?,?);";
    //    QString queryStr = "insert into `lf_bbs_reply`(pid,uid,title)values(:pid,:uid,:title);";
    QSqlQuery query(queryStr);

    //    //addBindValue按照顺序给字段赋值。
    //    query.addBindValue(22);
    //    query.addBindValue(99);
    //    query.addBindValue("dsf");

    query.bindValue(0,33);
    query.bindValue(1,33);
    query.bindValue(2,"aa");

    if(false == query.exec()){
        qDebug()<<"query failed:"<<query.lastError();
        return;
    }
    else{
        qDebug()<<"insertTable ok.";
    }

}

void SqlConnecter::insertTableList()
{
    QString queryStr = "insert into `lf_bbs_reply`(pid,uid,title)values(?,?,?)";
    //    QString queryStr = "insert into `lf_bbs_reply`(pid,uid,title)values(:pid,:uid,:title);";
    QSqlQuery query(queryStr);

    QVariantList pidList;
    pidList<<10<<11<<12;

    QVariantList uidList;
    uidList<<20<<21<<22;

    QVariantList titileList;
    titileList<<"batch 1"<<"batch 2"<<"batch 3";

    query.addBindValue(pidList);
    query.addBindValue(uidList);
    query.addBindValue(titileList);
    //execBatch批量操作
    if(false == query.execBatch()){
        qDebug()<<"insertTableList query failed:"<<query.lastError();
        return;
    }
    else{
        qDebug()<<"insertTableList query ok.";
    }

}

void SqlConnecter::transactionFunc()
{
#if 1
    //底层是否支持事务
    if(true == m_db.driver()->hasFeature(QSqlDriver::Transactions)){
        qDebug()<<"transaction true.";
    }
    else{
        qDebug()<<"not has transaction.";
        return;
    }
#endif

    if(true == QSqlDatabase::database().transaction()){
        QString queryStr = "insert into lf_bbs_reply (uid,title)values(?,?);";
        QSqlQuery query(queryStr);
        query.addBindValue(88);
        query.addBindValue(99);
        if (false == query.next()) {
            qDebug()<<"transaction false:"<<query.lastError();
        }else{
            qDebug()<<"transaction true.";
        }
        QSqlDatabase::database().commit();
    }else{
        qDebug()<<"transaction false.";
    }
}

void SqlConnecter::tableViewFunc()
{
    //    QSqlTableModel *model = new QSqlTableModel(parentObject, database);
    QSqlTableModel *model = new QSqlTableModel(nullptr,m_db);
    model->setTable("employee");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("Salary"));

    QTableView *view = new QTableView;
    view->setModel(model);
    view->hideColumn(0); // don't show the ID
    view->show();
}


