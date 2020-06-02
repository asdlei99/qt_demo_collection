#ifndef XEXCEL_H
#define XEXCEL_H

#include <QAxObject>
#include <QStringList>
#include <QList>

class XExcel
{
public:
    static XExcel & Instance()
    {
        static XExcel T;
        return T;
    }
    void saveList(QList<QStringList> &lines,QString sheetName="data");
    bool readList(QList<QStringList> &lines,QString sheetName="data");
    bool readList(QString &filepath,QList<QStringList> &lines,QString sheetName);

private:
    XExcel();
};

#endif // XEXCEL_H
