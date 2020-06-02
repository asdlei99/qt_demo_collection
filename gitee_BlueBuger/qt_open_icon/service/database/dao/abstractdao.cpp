/**
 ** @author:	    浓咖啡
 ** @date:            2016.10.21
 ** @brief:          dao层抽象接口
 */

#include "abstractdao.h"

/**
 * @brief 构造
 * @param name 表名字
 */
AbstractDao::AbstractDao(const QSqlDatabase &db, const QString &_tableName)
{
    qDebug("AbstractDao");
    this->db = db;
    tableName = _tableName;
}

/**
 * @brief 初始化表：如果表已经存在，那么返回true，如果不存在（首次使用），那么先创建，创建失败返回false
 * @return 成功返回true，失败返回false
 */
bool AbstractDao::initTable()
{
    QSqlQuery query(db);
    QString cmd = "select * from " + tableName;
    if(query.exec(cmd)){  //代表表已经存在
        qDebug()<<"table has exit";
        return true;
    }else{  //代表还没有表,先建立
        qDebug()<<tableName<<" hasn't exits, will create it";
        if(createTable()){
            qDebug()<<tableName<<" create success";
            return true;
        }else{  //创建表失败
            qDebug()<<tableName<<" create err";
            return false;
        }
    }
}

/**
 * @brief 相当于select * from table,会输出到打印台和控制台，以table名为文件名
 */
void AbstractDao::viewTable()
{
    QFile file(tableName + ".log");
    file.open(QIODevice::Text | QIODevice::WriteOnly);
    out.setDevice(&file);
    out<<left<<qSetFieldWidth(20);

    qDebug()<<endl;
    qDebug()<<"select * from "<<tableName;
    __viewTable();
    qDebug()<<endl;

    file.close();
}

/**
 * @brief 删除某条记录，这里抽象层只是提供一个方法，最好仍是针对不同实体单独封装
 * @param condition 删除条件
 */
void AbstractDao::deleteObj(const QString &condition)
{
    QSqlQuery query(db);
    QString cmd = "delete from " + tableName + " where " + condition;

    if(!query.exec(cmd)){
        qDebug()<<query.lastError();
    }
}
