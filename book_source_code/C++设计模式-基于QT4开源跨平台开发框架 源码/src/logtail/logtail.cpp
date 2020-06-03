#include "logtail.h"
#include <QDebug>

//start id=constructor
LogTail::LogTail(QString fn) {
    if (fn == QString()) {
        fn = "/var/log/apache/access.log";
    }
    connect (this, SIGNAL(readyReadStandardOutput()),
             this, SLOT(logOutput()));  /* When there is input ready, we will know about it.*/
    QStringList argv;
    argv << "-f" << fn; 
    // We want to exec "tail -f filename" 
    start("tail", argv);  /*  Returns  immediately, and now
                              there is a forked process running independently but "attached"
                              to this process. When the calling process exits the forked 
                              process will terminate. */
}

LogTail::~LogTail() {
    terminate();   /* Attempts to terminate this process. */
}
//end

//start id=logOutput
// tail sends its output to stdout.
void LogTail::logOutput() {  /* event driven - passive interface */
    QByteArray bytes = readAllStandardOutput();
    QStringList lines = QString(bytes).split("\n");
    foreach (QString line, lines) {
        qDebug() << line; 
    }
}
//end
//start id=main
#include <QApplication>
#include <logwindow.h>
#include <argumentlist.h>

int main (int argc, char* argv[]) {
    QApplication app(argc, argv);
    ArgumentList al;
    LogWindow lw("debug"); /* Create a scrolling edit window watching debug messages.*/
    lw.setWindowTitle("logtail demo");
    QString filename;
    if (al.size() > 1) filename = al[1];
    LogTail tail(filename); /* Create object, but start process too. */
    lw.show();
    return app.exec();
}
//end

