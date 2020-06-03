#include "movietimer.h"
#include <QDebug>
#include <QStringList>
#include <filevisitor.h>
#include <assertequals.h>


MovieTimer::~MovieTimer() {
    stop();
}


void MovieTimer::loadPics() {
    FileVisitor fv("*.jpg");
    connect (&fv, SIGNAL(foundFile(const QString&)),
             this, SLOT(addFile(const QString&)));
    fv.processEntry(":/images/"); /* We are using resources,
               which link binary files into the executable. They
               exist in a file system rooted at ":"
               See file: animate.qrc for list of embedded
               resources (.jpg files) */
}

void MovieTimer::addFile(const QString& filename) {
    pics << QPixmap(filename);
}

void MovieTimer::setInterval(int newDelay) {
    QTimer::setInterval(newDelay);
}

//start id=timer
MovieTimer::MovieTimer(): current(0) {
    setInterval(100);
    loadPics();
    connect(this, SIGNAL(timeout()), this, SLOT(nextFrame()));
}

void MovieTimer::nextFrame() {
    current = (current + 1) % pics.size();
    emit show(&pics[current]);
}
//end

