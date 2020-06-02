#ifndef DATABASE_H
#define DATABASE_H

#include "./common/common.h"


extern bool listDb(std::string url, std::string query, std::string body, mg_connection *c, OnRspCallback rsp_callback);
extern bool openDb(std::string url, std::string query, std::string body, mg_connection *c, OnRspCallback rsp_callback);
extern bool execSQL(std::string url, std::string query, std::string body, mg_connection *c, OnRspCallback rsp_callback);

class DataBase : public QObject
{
    Q_OBJECT
    SINGLETON(DataBase)
public:
    QJsonObject openDb(const QString &dbname);
    QJsonObject execSQL(const QString &sqlcmd);
    QJsonArray listDb() const;
    QString lastError() const {return m_lastError;}
private:
    QSqlDatabase m_db;
    QString m_lastError;
};

typedef Singleton<DataBase> SignletonDataBase;
#define DataBaseInstance SignletonDataBase::getInstance()


#endif // DATABASE_H
