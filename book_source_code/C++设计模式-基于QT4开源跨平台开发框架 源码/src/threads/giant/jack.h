#ifndef JACK_H
#define JACK_H

#include <QThread>
#include <QQueue>
#include <QStringList>


/* Jack is a trespasser in the giant's realm. All he does is
   search for stuff to steal from the giant. His search steps go into a
   fifo queue. If he finds something he says so and the giant can sort of hear him.  This demonstrates how to use queues
   as a means of passing messages between threads.
 
   */

class Jack :public QThread {
    Q_OBJECT

public:
    Jack();
    void run();

public slots:
    void setDelay(int newDelay);
    void killGiant();
signals:
    void chopBeanstalk();
private:
    QQueue<QString> m_Fifo;
    int m_Delay;
    bool m_BeanstalkChopped;        
    QStringList m_Stuff;  // list of stuff to steal
}
;

#endif

