#include "giant.h"
#include <QDebug>
#include <QStringList>

//start id="setup"

Giant::Giant() : m_Delay(1000), m_IsDead(false) {

    m_Fifo << "FEE FIE FO FUM";
    m_Fifo << "ho hum";
    m_Fifo << "I'm so sleeepy.";
    m_Fifo << "I really need a nap.\n";
}
//end


void Giant::setDelay(int newdelay) {
    m_Delay = newdelay;
}

//start id=slots
void Giant::die() {
    if (m_IsDead)
        return;
    m_IsDead = true;
    m_Fifo << "What? You nasty little worm.";
    m_Fifo << "I will squash you!!! ";
    m_Fifo << "So you're running back down the beanstalk.";
    m_Fifo << "I am coming right after you!";
    msleep(m_Delay);   /* Which thread is going to sleep here, the Giant
                                    or the MainThread? */
    m_Fifo << "Oh no!! Someone chopped the beanstalk!!";
    m_Fifo << "aaaaaaaaa!!! .........";
    m_Fifo << "   *splat* \n";
}

void Giant::hear(const QString &text) {
    QString t2 = ":" + text;
    m_Fifo << t2;
}

//end



/** A fifo processor with delays
    It simulates a slow-thinking giant,
    by deliberately placing delays between each dequeue 
    */
//start id=run
void Giant::run() {
    int zcount = 0;
    while (true) {
        zcount = 0;
        while (m_Fifo.isEmpty()) {
            msleep(m_Delay);
            ++zcount ;
            if (m_IsDead) {
                emit giantDead();
                break;
            }
            if (zcount > 3) {
                m_Fifo << "zzzzzz";
            }
        }
        QString message = m_Fifo.dequeue();
        msleep(m_Delay); 
        process(message);

    }
}

/** Observe, the inner workings of a giant's brain...
     Messages that begin with : are what the Giant can hear from Jack.
     Other messages are things he wants to say out loud.
     */
     
void Giant::process(QString message) {
    if (message.startsWith(":")) {
        QStringList l = message.split(":");
        msleep(m_Delay);
        if (! l[1].startsWith("(")) {
            QString msg = l[1];
            emit say ("Did I hear a mouse speak? It sounded like");
            emit say (distort(msg));
            emit say ("I never could understand those darned mice.");
            if (msg.startsWith("I FOUND")) {
                msg = msg.remove("I FOUND the ").remove("!!");
                msg = QString("Hey! Where is my %1?").arg(msg);
                emit say(msg);
            }
        }
    } else
        emit say(message);
}
//end

QString Giant::distort(QString text) {
    QString newstring = text;
    QString letterset1 = "aeidgmps";
    QString letterset2 = "ouytknbf";
    int len = letterset1.length();
    for (int i = 0; i < len; ++i)
        newstring.replace(letterset1[i], letterset2[i]);
    return newstring;
}

