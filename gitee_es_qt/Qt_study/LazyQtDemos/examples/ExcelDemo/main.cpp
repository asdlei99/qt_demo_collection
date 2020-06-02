#include <QCoreApplication>

#include <qt_windows.h>
#include <QAxObject>
#include "excel/ReadExcel.h"
#include <QDebug>

///
/// \brief 把QVariant转为QList<QList<QVariant> >
/// \param var
/// \param res
///
void castVariant2ListListVariant(const QVariant &var, QList<QList<QVariant> > &res)
{
    QVariantList varRows = var.toList();
    if(varRows.isEmpty())
    {
        return;
    }
    const int rowCount = varRows.size();
    QVariantList rowData;
    for(int i=0; i < rowCount; ++i)
    {
        rowData = varRows[i].toList();
        res.push_back(rowData);
    }
}

void printVariant(const QVariant &var)
{
    QVariantList varRows = var.toList();
    if(varRows.isEmpty())
    {
        return;
    }
    const int rowCount = varRows.size();
    qDebug("rowCount = %d", rowCount);
//    QVariantList rowData;

    int indexRow = 0, indexCol = 0;
    for (auto rowData: varRows) {
        indexRow++;
        QVariantList rowlist = rowData.toList();
        if (rowlist.isEmpty()) {
            break;
        }
        indexCol = 0;
        for (auto item: rowlist) {
            indexCol++;
            qDebug() << "(" << indexRow << "," << indexCol << ") = " << item;
        }
    }
}

void readExcelDemo(const QString &fileName)
{
    QAxObject *excel = new QAxObject("Excel.Application"); // 建立excel操作对象, 连接Excel控件


    excel->setProperty("Visible", false); // 不显示窗体看效果
    excel->setProperty("DisplayAlerts", false); //不显示警告看效果

    QAxObject *workbooks = excel->querySubObject("WorkBooks"); //获取工作簿(excel文件)集合
    workbooks->dynamicCall("Open(const QString&)", fileName);

    QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
    QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)",1);
    QAxObject *usedRange = worksheet->querySubObject("UsedRange");
    QVariant var = usedRange->dynamicCall("Value");//这里是所有的内容
    delete usedRange;

    printVariant(var);

    workbook->dynamicCall( "Close(Boolean)", false );
    excel->dynamicCall( "Quit(void)" );

    delete excel;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HRESULT r = OleInitialize(0); // 初始化ole
    if ( r != S_OK && r != S_FALSE) {
        qDebug("Qt: Could not initialize OLE (error %x)", (unsigned int)r);
    }
    QString fileName = QStringLiteral("E:\\src_works\\qt\\es_qt\\Qt_study\\LazyQtDemos\\除尘设备IO.xlsx");

//    readExcelDemo(fileName);
    ReadExcel excel;

    if (excel.openExcel(fileName)) {
        int row = 0, col = 0;
        excel.getInfo(row, col);
        for (int i = 0; i < row; i++) {
            for (int j =0; j < col; j++) {
                qDebug() << "(" << i << "," << j << ") = " << excel.getCellData(i, j);
            }
        }
    }


    OleUninitialize();  // 释放ole

    qDebug("finished!!!");
    return a.exec();
}
