#include "mainwindow.h"

#include <QApplication>
#include <qfile.h>
#include <qpdfwriter.h>
#include <QTextOption>
#include <qpainter.h>
#include <qdebug.h>
#include <qdatetime.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.show();

//    QString fileName = QDateTime::currentDateTime().toString("hh-mm-ss.zzz") + ".pdf";
    QString fileName = "out.pdf";
    qDebug()<<"fileName:"<<fileName;
    QFile pdfFile(fileName);
    if(false == pdfFile.open(QIODevice::WriteOnly)){
        qDebug()<<"open failed";
        return 0;
    }                 // 打开要写入的pdf文件
    QPdfWriter* pPdfWriter = new QPdfWriter(&pdfFile);  // 创建pdf写入器
    pPdfWriter->setPageSize(QPagedPaintDevice::A4);     // 设置纸张为A4
    pPdfWriter->setResolution(300);                     // 设置纸张的分辨率为300,因此其像素为3508X2479

    //demo 1
#if 0
    int iMargin = 60;                   // 页边距
    pPdfWriter->setPageMargins(QMarginsF(iMargin, iMargin, iMargin, iMargin));

    QPainter* pPdfPainter = new QPainter(pPdfWriter);   // qt绘制工具

    // 标题,居中
    QTextOption option(Qt::AlignHCenter | Qt::AlignVCenter);
    option.setWrapMode(QTextOption::WordWrap);

    // 标题上边留白
    int iTop = 100;

    // 文本宽度2100
    int iContentWidth = 2100;

    // 标题,22号字
    QFont font;
    font.setFamily("simhei.ttf");
    int fontSize = 22;
    font.setPointSize(fontSize);
    pPdfPainter->setFont(font);                    // 为绘制工具设置字体
    pPdfPainter->drawText(QRect(0, iTop, iContentWidth, 90),
//        QString::fromLocal8Bit("我的标题我骄傲"), option);
        QString("我的标题我骄傲"), option);
    // 内容,16号字，左对齐
    fontSize = 16;
    font.setPointSize(fontSize);
    pPdfPainter->setFont(font);
    option.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    iTop += 60;
    pPdfPainter->drawText(QRect(0, iTop, iContentWidth, 60),
//        QString::fromLocal8Bit("1、目录一"));
                          QString("1,目录一"));
    iTop += 60;
    // 左侧缩进2字符
    int iLeft = 120;
    pPdfPainter->drawText(QRect(iLeft, iTop, iContentWidth - iLeft, 60),
//        QString::fromLocal8Bit("我的目录一的内容。"), option);
                                  QString("我的目录一的内容。"), option);
    iTop += 60;
    pPdfPainter->drawText(QRect(0, iTop, iContentWidth, 60),
//                          QString::fromLocal8Bit("2、目录二"));
                                                    QString("2、目录二"));
    iTop += 60;
    pPdfPainter->drawText(QRect(iLeft, iTop, iContentWidth - iLeft, 60),
//        QString::fromLocal8Bit("我的目录一的内容"), option);
                                  QString("我的目录一的内容"), option);
      delete pPdfPainter;
#endif

    //demo 2
#if 1
    int iMargin = 60;                   // 页边距
    pPdfWriter->setPageMargins(QMarginsF(iMargin, iMargin, iMargin, iMargin));

    QPainter* pPdfPainter = new QPainter(pPdfWriter);   // qt绘制工具
    // 标题,居中
    QTextOption option(Qt::AlignHCenter | Qt::AlignVCenter);
    option.setWrapMode(QTextOption::WordWrap);

    //二维码
//    pPdfPainter->drawPixmap(1600,70,qrimage);
    //字体
    QFont font;
    font.setFamily("simhei.ttf");
    //标题，字号
    int fontSize = 22;
    font.setPointSize(fontSize);
    pPdfPainter->setFont(font);                    // 为绘制工具设置字体
    pPdfPainter->drawText(QRect(0, 0, 1980, 100),Qt::AlignHCenter|Qt::AlignBottom,
                          "青少年儿童健康体检表");
    //option.setWrapMode(QTextOption::WordWrap);
    //画表格

    pPdfPainter->setFont(QFont("", 10));
    pPdfPainter->drawText(20,180,"姓名：");
    pPdfPainter->drawText(500,180,"性别：");
    pPdfPainter->drawText(1000,180,"年龄：");
    pPdfPainter->drawText(20,250,"班级：");

    QDate date=QDate::currentDate();
    QString create_time=date.toString("yyyy/MM/dd");
    pPdfPainter->drawText(500,250,QString("体检日期：%1").arg(create_time));
//    pPdfPainter->drawText(20,320,QString("编号：%1").arg(str.at(i)));
        pPdfPainter->drawText(20,320,QString("编号：%1").arg(QDateTime::currentDateTime().toString(Qt::ISODate)));

    // 标题下边留白
    int iTop = 350;
    // 左侧缩进
    int iLeft = 20;
    // 设置画笔颜色、宽度
    //pPdfPainter.setPen(QPen(QColor(0, 160, 230), 2));
    pPdfPainter->setPen(2);
    // 设置画刷颜色
    //pPdfPainter->setBrush(QColor(255, 160, 90));
    pPdfPainter->drawRect(iLeft, iTop, 1980, 2750);//表格矩形方框
    pPdfPainter->drawLine(iLeft,iTop+100,iLeft+1980,iTop+100);
    pPdfPainter->drawLine(iLeft,iTop+500,iLeft+1980,iTop+500);
    pPdfPainter->drawLine(iLeft,iTop+1000,iLeft+1980,iTop+1000);
    pPdfPainter->drawLine(300,iTop,300,iTop+2750);
    pPdfPainter->drawText(iLeft+50,iTop+60,"检查项目");
    pPdfPainter->drawText(iLeft+900,iTop+60,"内容");
    pPdfPainter->drawText(iLeft+50,iTop+260,"体成分");
    pPdfPainter->drawText(iLeft+50,iTop+760,"脊柱");
    pPdfPainter->drawText(iLeft+50,iTop+1260,"骨龄");

    pPdfWriter->newPage();

    pPdfPainter->drawText(50,1260,"骨龄");

#endif
   delete pPdfPainter;
    delete pPdfWriter;
    pdfFile.close();

qDebug()<<"write ok.";

    return a.exec();
}
