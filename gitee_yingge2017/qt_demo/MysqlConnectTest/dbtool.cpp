#include "dbtool.h"

#include <QDebug>
#include <QDateTime>
#include <sstream>
#include <string>
#include <map>
#include <tuple>

//#include <cppconn/statement.h>
//#include <cppconn/resultset.h>
//#include <cppconn/prepared_statement.h>
//#include <cppconn/connection.h>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <mysql_error.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/config.h>

#include <sstream>

#include "threadpool.h"

using namespace std;

DbTool::DbTool()
{
    driver_ = sql::mysql::get_mysql_driver_instance();
    conn_ = nullptr;
}

DbTool*DbTool::Instance()
{
    static DbTool* S_instance = nullptr;
    if(S_instance == nullptr)
        S_instance = new DbTool();
    return S_instance;
}

bool DbTool::IsConnected()
{
    return conn_ != nullptr && conn_->isValid() && !conn_->isClosed();
}

bool DbTool::Connect(const string& ip, int port, const string& username, const string& password)
{
    ip_ = ip;
    port_ = port;
    username_ = username;
    password_ = password;

    stringstream ss_url;
    ss_url << "tcp://" << ip_ << ":" << port_;

    if(conn_ != nullptr)
        return false;
    //conn_ = driver_->connect("tcp://127.0.0.1:3306", "edq", "aaaaaa");
    conn_ = driver_->connect(ss_url.str(), username_, password_);
    if(conn_ == nullptr)
        return false;

    bool optionValue = true;
    conn_->setClientOption("OPT_RECONNECT", &optionValue);

    conn_->setSchema("elsp");


    return IsConnected();
}

void DbTool::Disconnect()
{
    if(conn_ != nullptr)
    {
        delete conn_;
        conn_ = nullptr;
    }
}

bool DbTool::execute(const string sql)
{
    try {
        RenLib::AutoSpinLock lk(mutext_);

        if(!conn_->isValid() || conn_->isClosed()) {
            if(!conn_->reconnect())
                return false;
            conn_->setSchema("elsp");
        }

        unique_ptr<sql::Statement> stmt(conn_->createStatement());
        if(!stmt)
            return false;

        stmt->execute("START TRANSACTION");
        stmt->execute(sql);
        stmt->execute("COMMIT");

        return true;
    } catch(sql::SQLException& e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << static_cast<const char*>(__FUNCTION__) << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        cout << "SQL: " << sql << endl;

        return false;
    } catch (...) {
        return false;
    }
}

sql::ResultSet *DbTool::query(const string &sql)
{
    try {
        RenLib::AutoSpinLock lk(mutext_);

        if(!conn_->isValid() || conn_->isClosed()) {
            if(!conn_->reconnect())
                return nullptr;
            conn_->setSchema("elsp");
        }

        unique_ptr<sql::Statement> stmt(conn_->createStatement());
        if(!stmt)
            return nullptr;

        return stmt->executeQuery(sql);
    } catch(sql::SQLException& e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << static_cast<const char*>(__FUNCTION__) << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        cout << "SQL: " << sql << endl;

        return nullptr;
    } catch (...) {
        return nullptr;
    }
}

void DbTool::queryAsync(const string &sql, const std::function<void (sql::ResultSet *)> &f)
{
    RenLib::ThreadPool::Instance()->ThreadCall([&](void*){
        sql::ResultSet * res = query(sql);
        f(res);
    }, nullptr);
}


