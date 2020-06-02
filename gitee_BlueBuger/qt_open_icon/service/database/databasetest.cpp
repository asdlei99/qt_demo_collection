/**
 ** @author:	    浓咖啡
 ** @date:            2016.10.23
 ** @brief:          数据库测试(service层):这里只是测试了基本框架完整性，对于多线程测试，可以另写测试用例
 */
#include "databasetest.h"

DatabaseTest::DatabaseTest()
{

}

void DatabaseTest::test()
{
    QSqlDatabase db = ConnectionPool::openConnection();

    StudentData data1;
    data1.setName("zhangsan");
    data1.setID(1);
    data1.setScore(90);

    StudentData data2;
    data2.setName("lisi");
    data2.setID(2);
    data2.setScore(95);

    StudentDaoImpl stuDao(db);
    stuDao.initTable();
    stuDao.insertObj(data1);
    stuDao.insertObj(data2);

    stuDao.deleteObj("id = 2");
    stuDao.viewTable();

    ConnectionPool::release(); // 程序结束时关闭连接，以免造成连接泄漏
}
