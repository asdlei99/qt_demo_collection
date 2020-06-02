/**
 ** @author:	    浓咖啡
 ** @date:            2016.10.23
 ** @brief:          数据库测试(service层):这里只是测试了基本框架完整性，对于多线程测试，可以另写测试用例
 */

#ifndef DATABASETEST_H
#define DATABASETEST_H

#include "connectionpool.h"
#include "studentdaoimpl.h"

class DatabaseTest
{
public:
    DatabaseTest();
    void test();
};

#endif // DATABASETEST_H
