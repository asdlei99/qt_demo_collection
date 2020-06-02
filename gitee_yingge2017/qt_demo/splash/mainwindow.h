#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qwidget.h>
#include <qlabel.h>
#include <qmovie.h>
#include <QSharedMemory>
#include <qfile.h>
#include <QTextStream>

class SplashWidget:public QWidget{
    Q_OBJECT
public:
    SplashWidget();
    ~SplashWidget();

    void setElapsedMs(const int ms = 2000);
    void setShareMemoryReadMs(const int ms = 200);
    void writeLog(const QString s);
signals:
    void sigQuit();
protected:
    void timerEvent(QTimerEvent * event);
    void showEvent(QShowEvent *);
private:
    QLabel *m_label;
    QMovie *m_movie;
    QSharedMemory *m_sm;
    int m_elapseMs;
    int m_elapseTimerId,m_shareMemoryReadId;
    QFile *m_file;
    QTextStream m_textStream;
};

#endif // MAINWINDOW_H
