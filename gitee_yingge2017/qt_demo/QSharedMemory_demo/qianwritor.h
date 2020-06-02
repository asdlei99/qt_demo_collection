#ifndef QIANWRITOR_H
#define QIANWRITOR_H

#include <QObject>
#include <QSharedMemory>

class QianWritor : public QObject
{
    Q_OBJECT
public:
    explicit QianWritor(QObject *parent = nullptr);
    ~QianWritor();
signals:

public slots:
protected:
    void timerEvent(QTimerEvent*e);
private:
    QSharedMemory *m_sm;
};

#endif // QIANWRITOR_H
