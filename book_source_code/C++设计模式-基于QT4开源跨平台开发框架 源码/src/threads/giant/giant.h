#ifndef GIANT_H
#define GIANT_H

#include <QThread>
#include <QQueue>
#include <QString>


/* A fierce angry giant. All he does is yell into a
   fifo queue. This demonstrates how to use queues
   as a means of passing messages between threads.
   */
//start
class Giant :public QThread {
    Q_OBJECT
  public:
    Giant();
    void run();
  public slots:
    void hear(const QString& text); 
    void die();
    void setDelay(int newDelay);
  signals:
    void say(QString line);
    void small(QString line);
    void giantDead();
  private:
    void process(QString message);
    QString distort(QString text);
    QQueue<QString> m_Fifo;
    int m_Delay;
    bool m_IsDead;    
};
//end
#endif

