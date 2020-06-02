#include "database.h"

#define DB_PATH QString(R"(./db)")

#define LOG() qDebug() << __FUNCTION__ << __LINE__ << ":"

DataBase::DataBase():
    QObject(nullptr)
{
}

DataBase::~DataBase()
{
}

QJsonObject DataBase::openDb(const QString &dbname)
{
    QJsonObject jobj;
    m_db = QSqlDatabase::addDatabase("QSQLITE",dbname);
    m_db.setDatabaseName(DB_PATH+"/"+dbname);

    if(!m_db.open())
    {
        m_lastError = m_db.lastError().text();
        jobj.insert("code",-1);
        jobj.insert("text",m_lastError);
    }else
    {
        jobj.insert("code",0);
    }
    return jobj;
}

QJsonObject DataBase::execSQL(const QString &sqlcmd)
{
    QJsonArray jarr;
    QJsonObject obj;
    QSqlQuery query(m_db);

    QString sql = sqlcmd;
    if(sqlcmd.startsWith("select"))
    {
        sql.append(" limit 100");
    }

    sql.append(";");
    auto r = query.exec(sql);
    LOG() << sql << r;
    while(query.next())
    {
        QJsonArray rows;
        for(int i = 0; i < query.record().count();i++)
        {
            rows.append( query.value(i).toString());
        }
        jarr.append(rows);
        LOG() << rows;
    }

    if(r)
        obj.insert("code",0);
    else
    {
        obj.insert("code",-1);
        obj.insert("text",query.lastError().text());
    }

    obj.insert("rows",jarr);
    return obj;
}

QJsonArray DataBase::listDb() const
{
    QDir dir(DB_PATH);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();
    QJsonArray jarr;
    for(int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        jarr.append(fileInfo.fileName());
    }
    return jarr;
}

bool listDb(std::string url, std::string query, std::string body, mg_connection *c, OnRspCallback rsp_callback)
{
    auto jarr = DataBaseInstance.listDb();
    QJsonDocument jdoc;
    jdoc.setArray(jarr);
    std::string jstr = QString(jdoc.toJson(QJsonDocument::Compact)).toStdString();
    rsp_callback(c, jstr);
    std::cout << __FUNCTION__ << " " << jstr;
}

bool openDb(std::string url, std::string query, std::string body, mg_connection *c, OnRspCallback rsp_callback)
{
    std::cout << "url: " << url << std::endl;
    std::cout << "query: " << query << std::endl;
    std::cout << "body: " << body << std::endl;

    auto dbname = QString::fromStdString(query).remove("name=");
    auto res = DataBaseInstance.openDb(dbname);
    QJsonDocument jdoc;
    jdoc.setObject(res);
    std::string jstr =  QString(jdoc.toJson(QJsonDocument::Compact)).toStdString();
    rsp_callback(c, jstr);
    std::cout << __FUNCTION__ << " " << jstr << std::endl;
    return true;
}


bool execSQL(std::string url, std::string query, std::string body, mg_connection *c, OnRspCallback rsp_callback)
{
    std::cout << "url: " << url << std::endl;
    std::cout << "query: " << query << std::endl;
    std::cout << "body: " << body << std::endl;

    QUrlQuery q(QString::fromStdString(query));
    auto sql = q.queryItemValue("sql",QUrl::FullyDecoded);
    sql.replace("+"," ");

    auto res = DataBaseInstance.execSQL(sql);

    QJsonDocument jdoc;
    jdoc.setObject(res);
    std::string jstr =  QString(jdoc.toJson(QJsonDocument::Compact)).toStdString();
    rsp_callback(c, jstr);
    std::cout << __FUNCTION__ << " " << jstr << std::endl;
    return true;
}
