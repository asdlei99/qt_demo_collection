#include "jack.h"
#include <stdlib.h>   // for random function
#include <QDebug>
#include <QStringList>
#include <QInputDialog>
#include <logger.h>


Jack::Jack() :  m_Delay(1000), m_BeanstalkChopped(false) {
    m_Stuff << "magic harp" << "goose that lays golden eggs"
           << "magic hamster" << "killer rabbit" << "singing fly" ;
}

void Jack::setDelay(int newdelay) {
    m_Delay = newdelay;
}

void Jack::killGiant() {
    if (!m_BeanstalkChopped) {
        m_BeanstalkChopped = true;
        Logger* l = Logger::getLogger("jack");
        m_Stuff.clear();
        m_Fifo.clear();
        l->info("(Chopping down the beanstalk...)");
        emit chopBeanstalk();
//        l->info(QString("Say good night, giant!"));
    }
}


void Jack::run() {
    Logger* l = Logger::getLogger("jack");
    int q = 4;  // for setting probability of finding an item.
    srandom(time(0));   // seed the random function
    int i(0);
    l->info("Wow! I'm in the giant's house. I can steal his stuff.");
    msleep(2 * m_Delay);  
    while (m_Stuff.count()) {
        msleep(m_Delay);        
        if (m_Fifo.isEmpty()) {
            msleep(m_Delay*2);
            i = 0;
            foreach (QString s, m_Stuff)
                m_Fifo << s;
            continue;
        }
        QString item = m_Fifo.dequeue();
        if (random() < RAND_MAX/q) {
            i = m_Stuff.indexOf(item);
            m_Stuff.removeAt(i);
            item = "I FOUND the " + item + "!!";
        }
        else
            item = "(searching for the " + item + " ...)";
        l->info(item);
        msleep(2);
    }
    killGiant();
}

