#include "ReadExcel.h"

#include <QFile>

ReadExcel::ReadExcel()
    :m_row(0), m_col(0), m_filename("")
{
    m_excel = new QAxObject("Excel.Application"); // 建立excel操作对象, 连接Excel控件
}

ReadExcel::~ReadExcel()
{
    if (!m_mapdata.empty()) {
        m_mapdata.clear();
    }
    delete m_excel;
}

bool ReadExcel::openExcel(const QString &filename)
{
    if (filename.isEmpty()) {
        m_row = 0;
        m_col = 0;
        return false;
    }

    QFile file(filename);
    if (!file.exists()) {
        m_row = 0;
        m_col = 0;
        return false;
    }

    if (!m_mapdata.empty()) {
        m_mapdata.clear();
    }
    m_filename = filename;
    try {
//        getALLfromExcel();
        readAllFromExcel(m_filename);
    } catch (...) {
        return false;
    }

    return true;
}

void ReadExcel::getInfo(int &row, int &col) const
{
    row = m_row;
    col = m_col;
}

QVariant ReadExcel::getCellData(const int &row, const int &col)
{
    if (row >= 1 && row <= m_row && col >= 1 && col <= m_col) {
        p.m_row = row;
        p.m_col = col;
        return m_mapdata[p];
    } else {
        return QVariant(QVariant::Invalid);
    }
}

void ReadExcel::getALLfromExcel()
{
    m_excel->setProperty("Visible", 0);
    QAxObject* workbooks = m_excel->querySubObject("WorkBooks");
    workbooks->dynamicCall("Open (const QString&)", m_filename);
    QAxObject* workbook = m_excel->querySubObject("ActiveWorkBook");
//    QAxObject* worksheets = workbook->querySubObject("WorkSheets");
    QAxObject* worksheet = workbook->querySubObject("Worksheets(int)", 1); //worksheet number
    QAxObject* usedrange = worksheet->querySubObject("UsedRange");
    QAxObject* rows = usedrange->querySubObject("Rows");
    QAxObject* columns = usedrange->querySubObject("Columns");
    int intRowStart = usedrange->property("Row").toInt();
    int intColStart = usedrange->property("Column").toInt();
    int intCols = columns->property("Count").toInt();
    int intRows = rows->property("Count").toInt();
    m_row = intRows;
    m_col = intCols;
    QAxObject * cell;
    for (int i = intRowStart; i < intRowStart + intRows; i++)
    {
        for (int j = intColStart; j < intColStart + intCols; j++)
        {
            Position pos(i, j);
            cell = m_excel->querySubObject("Cells(Int, Int)", i, j );
            QVariant cellValue = cell->dynamicCall("value");
            m_mapdata.insert(pos, cellValue);
        }
    }
    m_excel->setProperty("DisplayAlerts", 0);
    workbook->dynamicCall("Save(void)");
    workbook->dynamicCall("Close (Boolean)", false);
    m_excel->setProperty("DisplayAlerts",1);
}


void ReadExcel::readAllFromExcel(const QString &filename)
{
//    QAxObject *excel = new QAxObject("Excel.Application"); // 建立excel操作对象, 连接Excel控件

    m_excel->setProperty("Visible", false); // 不显示窗体看效果
    m_excel->setProperty("DisplayAlerts", false); //不显示警告看效果

    QAxObject *workbooks = m_excel->querySubObject("WorkBooks"); //获取工作簿(excel文件)集合
    workbooks->dynamicCall("Open(const QString&)", filename);

    QAxObject *workbook = m_excel->querySubObject("ActiveWorkBook");
    QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)",1);
    QAxObject *usedrange = worksheet->querySubObject("UsedRange");
    // read rows and cols
    QAxObject* rows = usedrange->querySubObject("Rows");
    QAxObject* columns = usedrange->querySubObject("Columns");
//    int intRowStart = usedrange->property("Row").toInt();
//    int intColStart = usedrange->property("Column").toInt();
    int intCols = columns->property("Count").toInt();
    int intRows = rows->property("Count").toInt();
    m_row = intRows;
    m_col = intCols;

    QVariant var = usedrange->dynamicCall("Value");//这里是所有的内容
    delete usedrange;


//    printVariant(var);

    workbook->dynamicCall( "Close(Boolean)", false );
    m_excel->dynamicCall( "Quit(void)" );

//    delete excel;
}


void ReadExcel::castVariant2Map(const QVariant &var)
{
    QVariantList varRows = var.toList();
    if(varRows.isEmpty())
    {
        return;
    }

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
            Position pos(indexRow, indexCol);
            m_mapdata.insert(pos, item);
//            qDebug() << "(" << indexRow << "," << indexCol << ") = " << item;
        }
    }
}
