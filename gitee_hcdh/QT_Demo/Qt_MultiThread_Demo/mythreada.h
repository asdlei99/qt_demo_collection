#ifndef MYTHREADA_H
#define MYTHREADA_H
#include <QThread>
#include <QDebug>

class myThreadA : public QThread
{
public:
    myThreadA(QString Text, int DelayMs);
    void run();

private:
    QString m_strText;  //接受主线程设置的传递文本参数
    int m_nDelayMs;     //接受主线程设置的线程休眠时间ms
};

#endif // MYTHREADA_H
