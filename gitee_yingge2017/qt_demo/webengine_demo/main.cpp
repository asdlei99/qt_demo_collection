#include "mainwindow.h"
#include <QApplication>
#include <QWebEngineView>
#include <QGuiApplication>
#include <qstring.h>

#include "interactive.h"
#include "inspector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();

#if 0
    QWebEngineView *webView = new QWebEngineView;
    webView->load(QUrl("https://www.baidu.com"));
    webView->show();
#endif
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "1112");
    QWebEngineView *webView = new QWebEngineView;
    //    webView->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    //    QString urlStr = "d:/gitfile/qt_demo/webengine_demo/resource/go.html";
    //    QString urlStr = "d:/gitfile/qt_demo/webengine_demo/resource/statistics.html?taskId=fcfe0337d2bf4e24955fcb3fa5d796ee&subjectId=1";
    QString urlStr = "d:/gitfile/qt_demo/webengine_demo/resource/index.html";
//    QString urlStr = "d:/gitfile/qt_demo/webengine_demo/resource/answerProgress.html";

    webView->load(QUrl(QString("file:///") + urlStr));


    //    Interactive *it = new Interactive;

    //    QObject::connect(it,Interactive::sigSend,
    //                     it,Interactive::slotRev);


    //    QObject::connect(it,Interactive::sigSend( const QString),
    //                     it,Interactive::slotRev(QStirng));

    QObject::connect(webView->page(), &QWebEnginePage::loadFinished,
                     [&]{
        qDebug()<<"loadFinished-----------------";
                webView->page()->runJavaScript("setBaseData({})");
        webView->page()->runJavaScript("update()");
    });


#if 0
    QUrl url("qrc://resource/index.html");
    if(false == url.isValid()){
        qDebug()<<"url not valid";
    }else{
        qDebug()<<"url valid";
    }
    webView->load(url);

#endif
    //        webView->load(QUrl("qrc://resource/index.html"));

    webView->show();
    //    webView->page()->runJavaScript("clickme");
    //    webView->page()->runJavaScript("update");
    qDebug()<<webView->contentsRect();


   Inspector *ip = new Inspector;
   ip->show();

    return a.exec();
}
