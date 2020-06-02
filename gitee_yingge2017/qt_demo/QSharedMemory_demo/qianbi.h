#ifndef QIANBI_H
#define QIANBI_H

#include <QObject>
#include <QTimerEvent>

class Qianbi:public QObject
{
    Q_OBJECT
public:
    Qianbi(QObject *parent = nullptr);
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // QIANBI_H
