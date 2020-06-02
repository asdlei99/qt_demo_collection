#include "odbcconnector.h"

#include <qsqlerror.h>
#include <qdebug.h>

ODBCConnector::ODBCConnector()
{
    connect();
}

void ODBCConnector::connect()
{
    m_db = QSqlDatabase::addDatabase("QODBC");

//    db.setHostName("192.168.110.126");
//    db.setPort(3306);

//    db.setUserName("edq");
//    db.setPassword("aaaaaa");

    m_db.setDatabaseName("mytest");

    if (!m_db.open()){
        qDebug()<<"cannot open.";
        qDebug()<<"connectOptions:"<<m_db.connectOptions();
        qDebug()<<"driverName:"<<m_db.driverName();
        qDebug()<<"error:"<<m_db.lastError().text();
    }
    else{
        qDebug()<<"open.";
    }
}
