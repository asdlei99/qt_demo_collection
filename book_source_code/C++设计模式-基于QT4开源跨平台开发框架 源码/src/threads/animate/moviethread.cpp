#include "moviethread.h"
#include <QDebug>
#include <QStringList>
#include <filevisitor.h>
#include <assertequals.h>

MovieThread::MovieThread() : m_Delay(100) {
    loadPics();
}
void MovieThread::setInterval(int newdelay) {
    m_Delay = newdelay;
}

MovieThread::~MovieThread() {
    terminate();
}

//start id="pixmaps"

void MovieThread::loadPics() {
    FileVisitor fv("*.jpg");
    connect (&fv, SIGNAL(foundFile(const QString&)),
             this, SLOT(addFile(const QString&)));
    fv.processEntry(":/images/"); /* We are using resources,
           which link binary files into the executable. They
           exist in a file system rooted at ":"
           See file: animate.qrc for list of embedded
           resources (.jpg files) */
}

void MovieThread::addFile(const QString& filename) {
    m_Pics << QPixmap(filename);
}
//end

//start id="wait"

void MovieThread::stop() {
    terminate();
    wait(5000);
}

//end

//start id="run"
void MovieThread::run() {
    int current(0), picCount(m_Pics.size());
    while (true) {
        msleep(m_Delay);   
        emit show(&m_Pics[current]);
        current = (current + 1) % picCount; 
    }
}

//end


