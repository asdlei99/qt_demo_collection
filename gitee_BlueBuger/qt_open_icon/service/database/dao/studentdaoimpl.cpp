/**
 ** @author:	    浓咖啡
 ** @date:            2016.10.23
 ** @brief:          学生信息dao层演示示例
 */

#include "studentdaoimpl.h"

#define TABLE_NAME QString("student_table")

#define CREATE_TABLE_CMD "create table "+TABLE_NAME+"(\
id int primary key,   \
name text not null,\
score real not null)"

#define INSERT_CMD "insert into "+TABLE_NAME+"\
(id,name,score)\
values(:id,:name,:score)"

/**
 * @brief 构造函数
 * @param db 数据库连接
 */
StudentDaoImpl::StudentDaoImpl(const QSqlDatabase &db) : AbstractDao(db, TABLE_NAME)
{
    qDebug()<<CREATE_TABLE_CMD;
}

/**
 * @brief 产生所需的表
 * @return
 */
bool StudentDaoImpl::createTable()
{
    qDebug()<<"StudentDaoImpl::createTable";
    QSqlQuery query(db);
    if(!query.exec(CREATE_TABLE_CMD)){
        qDebug()<<query.lastError();
        return false;
    }else{
        return true;
    }
}

/**
 * @brief 插入数据
 * @param obj 学生实体信息
 * @return
 */
bool StudentDaoImpl::insertObj(StudentData &obj)
{
    QSqlQuery query(db);
    query.prepare(INSERT_CMD);
    query.bindValue(":id", obj.getID());
    query.bindValue(":name", obj.getName());
    query.bindValue(":score", obj.getScore());
    if(!query.exec()){
        qDebug()<<query.lastError();
        return false;
    }else{
        return true;
    }
}

/**
 * @brief 插入多个数据
 * @param 学生信息链表
 * @return
 */
bool StudentDaoImpl::insertObjList(QList<StudentData> &objList)
{
    StudentData obj;
    QSqlQuery query(db);
    query.prepare(INSERT_CMD);

    for(int i=0; i<objList.length(); i++){
        obj = objList.at(i);
        query.bindValue(":id", obj.getID());
        query.bindValue(":name", obj.getName());
        query.bindValue(":score", obj.getScore());

        if(!query.exec()){
            qDebug()<<query.lastError();
            return false;
        }
    }
    return true;
}

/**
 * @brief 查看表的内容
 */
void StudentDaoImpl::__viewTable()
{
    QString cmd = "select * from " + TABLE_NAME;
    QSqlQuery query(db);
    query.exec(cmd);

    //输出字段名
    //输出到控制台，这个格式不好控制，如果数据多，可以去文件查看
    qDebug()<<\
               "id"<<\
               "name"<<\
               "score";

    //输出到文件
    out<<\
          "id"<<\
          "name"<<\
          "score"<<qSetFieldWidth(0)<<endl;

    //输出数据
    while (query.next()) {
        //输出到控制台
        qDebug()<<\
                   query.value(0).toInt()<<\
                   query.value(1).toString()<<\
                   query.value(2).toInt();
        //输出到文件
        out<<left<<qSetFieldWidth(20)<<\
             query.value(0).toInt()<<\
             query.value(1).toString()<<\
             query.value(2).toInt()<<qSetFieldWidth(0)<<endl;
    }
}
