#ifndef SQLCONNECTER_H
#define SQLCONNECTER_H

#include <QObject>
#include <qsqldatabase.h>
#include <qmap.h>

class SqlConnecter : public QObject
{
    Q_OBJECT
public:
    explicit SqlConnecter(QObject *parent = nullptr);
    ~SqlConnecter();


private:
    void selectTable(const QString tableName);

signals:

private:
    void selectAll(const QString tableName);
    //获取表字段名
    void getColumnNames(const QString tableName);
    void descTable(const QString tableName);
    //lf_bbs_reply
    void insertTable();
    //列表插入
    void insertTableList();
    //事务操作
    void transactionFunc();

    void tableViewFunc();
private:
    QSqlDatabase m_db;
};

#endif // SQLCONNECTER_H
