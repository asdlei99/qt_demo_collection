#include <QApplication>
#include "ConnectionPool.h"
#include "actualdatadaoimpl.h"
#include "studentdaoimpl.h"

/**
 * @brief 这一层相当于service层，只专注于逻辑，可以用多线程测试连接池
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 0
    ActualData data;
    data.setRecordTime("2016-5.31");
    data.setGivenCurrent(1);
    data.setGivenVoltage(2);
    data.setWeldCurrent(3);
    data.setWeldVoltage(4);
    data.setWeldMode(5);
    data.setMaterial(6);
    data.setDiameter(7);
    data.setWeldStatus(8);
    data.setAlarm(9);
    data.setWireSpeed(10);

    ActualData data1;
    data1.setRecordTime("2016-8.31");
    data1.setGivenCurrent(11);
    data1.setGivenVoltage(22);
    data1.setWeldCurrent(31);
    data1.setWeldVoltage(45);
    data1.setWeldMode(5);
    data1.setMaterial(6);
    data1.setDiameter(7);
    data1.setWeldStatus(8);
    data1.setAlarm(9);
    data1.setWireSpeed(10);

    QSqlDatabase db = ConnectionPool::openConnection();
    ActualDataDaoImpl actServer(db);
    actServer.initTable();
    actServer.insertObj(data);
    actServer.insertObj(data1);

    actServer.viewTable();
#endif

    StudentData data1;
    data1.setName("zhangsan");
    data1.setID(1);
    data1.setScore(90);

    StudentData data2;
    data2.setName("lisi");
    data2.setID(2);
    data2.setScore(95);

    QSqlDatabase db = ConnectionPool::openConnection();
    StudentDaoImpl stuDao(db);
    stuDao.initTable();
    stuDao.insertObj(data1);
    stuDao.insertObj(data2);
    stuDao.viewTable();

    ConnectionPool::release(); // 程序结束时关闭连接，以免造成连接泄漏
}
