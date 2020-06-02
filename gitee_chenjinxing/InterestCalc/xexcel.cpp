#include "xexcel.h"
#include <QFileDialog>

void XExcel::saveList(QList<QStringList> &lines, QString sheetName)
{
    QString filepath=QFileDialog::getSaveFileName(0,"Save orbit",".","Microsoft Office 2007 (*.xlsx)");//获取保存路径
    if(!filepath.isEmpty()){
        QAxObject *excel = new QAxObject();
        excel->setControl("Excel.Application");//连接Excel控件
        excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
        excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示

        QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
        workbooks->dynamicCall("Add");//新建一个工作簿
        QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
        QAxObject *worksheets = workbook->querySubObject("Sheets");//获取工作表集合
        QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);//获取工作表集合的工作表1，即sheet1
        for(int i  =1;i <=lines.size();i++)
        {
            for(int j =1;j <=lines.at(i-1).size();j++)
            {
                QAxObject* cell = worksheet->querySubObject("Cells(int, int)", i, j);  //获单元格值
                cell->dynamicCall("SetValue(const QVariant&)",QVariant(lines.at(i-1).at(j-1)));//设置单元格的值
            }
        }

        workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了。
        workbook->dynamicCall("Close()");//关闭工作簿
        excel->dynamicCall("Quit()");//关闭excel
        delete excel;
        excel=NULL;
    }

}

bool XExcel::readList(QList<QStringList> &lines, QString sheetName)
{
    QString filepath= QFileDialog::getOpenFileName(0,"Save orbit",".","Microsoft Office 2007 (*.xlsx)");
    return readList(filepath,lines,sheetName);
}

bool XExcel::readList(QString &filepath, QList<QStringList> &lines, QString sheetName)
{
    if(!filepath.isEmpty()){
        QAxObject* excel = new QAxObject("Excel.Application");
        excel->setProperty("Visible", false);
        QAxObject* workbooks = excel->querySubObject("WorkBooks");
        workbooks->dynamicCall("Open (const QString&)", filepath); //filename
        QAxObject* workbook = excel->querySubObject("ActiveWorkBook");
        QAxObject* worksheets = workbook->querySubObject("WorkSheets");
        QAxObject* worksheet = workbook->querySubObject("Worksheets(int)", 1); //worksheet number
        QAxObject* usedrange = worksheet->querySubObject("UsedRange");
        QAxObject* rows = usedrange->querySubObject("Rows");
        QAxObject* columns = usedrange->querySubObject("Columns");
        int intRowStart = usedrange->property("Row").toInt();
        int intColStart = usedrange->property("Column").toInt();
        int intCols = columns->property("Count").toInt();
        int intRows = rows->property("Count").toInt();
        QAxObject * cell;
        for (int i = intRowStart; i < intRowStart + intRows; i++)
        {
            QStringList line;
            for (int j = intColStart; j < intColStart + intCols; j++)
            {
                cell = excel->querySubObject("Cells(Int, Int)", i, j );
                QVariant cellValue = cell->dynamicCall("value");
                line.append(cellValue.toString());
            }
            lines.push_back(line);
        }
        excel->setProperty("DisplayAlerts", 0);
        workbook->dynamicCall("Save(void)");
        workbook->dynamicCall("Close (Boolean)", false);
        excel->setProperty("DisplayAlerts",1);

        delete excel;
        return true;
    }
    return false;
}

XExcel::XExcel()
{

}
