#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <string>

class Connector
{
public:
    Connector();

    bool IsConnected();
    bool Connect(const std::string& ip, int port, const std::string& username, const std::string& password);
private:
    sql::mysql::MySQL_Driver* driver_;
    sql::Connection* conn_;

    std::string ip_;
    int port_;
    std::string username_;
    std::string password_;


};

#endif // CONNECTOR_H
