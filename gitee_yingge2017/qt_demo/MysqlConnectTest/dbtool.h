#ifndef DBTOOL_H
#define DBTOOL_H

#include "threadpool.h"
#include "spinlock.h"

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <mysql_error.h>
#include <cppconn/resultset.h>
//#include <common/spinlock.hpp>

#include <string>
#include <vector>
#include <QMap>

class DbTool
{
public:
    DbTool();
    static DbTool* Instance();

public:
    bool IsConnected();
    bool Connect(const std::string& ip, int port, const std::string& username, const std::string& password);
    void Disconnect();

private:
    sql::mysql::MySQL_Driver* driver_;
    sql::Connection* conn_;

    std::string ip_;
    int port_;
    std::string username_;
    std::string password_;

    RenLib::SpinMutex mutext_;

    bool execute(const std::string sql);
    sql::ResultSet *query(const std::string& sql);
    void queryAsync(const std::string& sql, const std::function<void (sql::ResultSet*)>& f);

};

#endif // DBTOOL_H
