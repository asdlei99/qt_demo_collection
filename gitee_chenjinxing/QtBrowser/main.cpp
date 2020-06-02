#include "webwidget.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QDebug>
#include <QRegExp>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QString testStr ="[{\"id\":\"ae5af2c6e1c1454c8435b0b7a1524afc\"";
//    qDebug()<<testStr;
//    qDebug()<<testStr.replace(QRegExp("\\\""),"\"");
//    qDebug()<<testStr.replace(QRegExp("\\"),"");
//    qDebug()<<testStr.replace("\\","");
//    qDebug()<<testStr.remove("\\");
//    qDebug()<<testStr.remove('\\');
//    return  a.exec();

    WebWidget * w =new WebWidget();

    QVBoxLayout *layout =new QVBoxLayout();
    layout->addWidget(w);

    QWidget *mainw =new QWidget();
    mainw->setAttribute(Qt::WA_DeleteOnClose,true);
    mainw->setLayout(layout);
    mainw->show();

    return a.exec();
}
