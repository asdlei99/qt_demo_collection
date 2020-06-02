#include "connector.h"

#include <sstream>
#include <string>
#include <qdebug.h>

using namespace std;

Connector::Connector()
{
    string ip = "127.0.0.1";
    int port = 3306;
    string username = "laowang";
    string password = "laowang";

    if(false == Connect(ip,port,username,password)){
        qDebug()<<"Mysql connect failed.";
    }

#if 0
    sql::mysql::MySQL_Driver* driver_;
    sql::Connection* conn_;

    driver_ = sql::mysql::get_mysql_driver_instance();
    conn_ = nullptr;


    //conn_ = driver_->connect("tcp://127.0.0.1:3306", "edq", "aaaaaa");
    sql::Connection * connect(const sql::SQLString& hostName, const sql::SQLString& userName, const sql::SQLString& password);
//    conn_ = driver_->connect(ss_url.str(), username_, password_);
//    if(conn_ == nullptr)
//        return false;

    bool optionValue = true;
    conn_->setClientOption("OPT_RECONNECT", &optionValue);

    conn_->setSchema("elsp");
#endif
}

bool Connector::IsConnected()
{
    return conn_ != nullptr && conn_->isValid() && !conn_->isClosed();
}

bool Connector::Connect(const std::string &ip, int port, const std::string &username, const std::string &password)
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

