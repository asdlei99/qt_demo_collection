/**
 ** @author:	    浓咖啡
 ** @date:            2016.10.21
 ** @brief:          dao层抽象接口
 */

#ifndef ABSTRACTDAO_H
#define ABSTRACTDAO_H

#include  <QtSql>

class AbstractDao : public QObject
{
    Q_OBJECT
public:
    explicit AbstractDao(const QSqlDatabase &db, const QString &_tableName);

    bool initTable();  //初始化所需要的表
    void viewTable();  //相当于select * from table,会输出到打印台和控制台，以table名为文件名
    void deleteObj(const QString &condition);

protected:
    virtual bool createTable() = 0;  //产生表的接口
    virtual void __viewTable() = 0;  //select * from table封装

    //下面都是子类必须提供接口，但是由于参数不定，模板方式又会增加代码复杂度
    //virtual bool insertObj(ObjType &obj) = 0;
    //virtual bool insertObjList(QList<ObjType> &objList) = 0;

    QSqlDatabase db;
    QString tableName;
    QTextStream out;
};

#endif // ABSTRACTDAO_H
