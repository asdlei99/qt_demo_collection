#ifndef ODBCCONNECTOR_H
#define ODBCCONNECTOR_H

#include <qsqldatabase.h>

class ODBCConnector
{
public:
    ODBCConnector();
    void connect();
private:
    QSqlDatabase m_db;
};

#endif // ODBCCONNECTOR_H
