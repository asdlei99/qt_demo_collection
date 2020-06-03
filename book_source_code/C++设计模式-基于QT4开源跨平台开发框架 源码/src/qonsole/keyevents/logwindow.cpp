#include "logwindow.h"
#include "logger.h"

#include <QScrollBar>
#include <qstd.h>
using namespace qstd;

LogWindow::LogWindow( QString logname, QWidget* parent) :
QTextEdit(parent), shouldScroll(10) {
    setReadOnly(true);
    if (logname != QString()) {
        log(logname);
    }
    
}

void LogWindow::log(QString logname) {
    
    Logger *l = Logger::getLogger(logname);
    connect(l, SIGNAL(data(QString)), this, SLOT(append(QString)));
    QScrollBar* vsb = verticalScrollBar () ;
    setLineWrapMode(QTextEdit::NoWrap);
    vsb->connect(vsb, SIGNAL(sliderMoved(int)), this, SLOT(checkScroll(int)));
}


void LogWindow::checkScroll(int newValue) {
    QScrollBar *vsb = verticalScrollBar();
    if (!vsb->isVisible()) return;
    if (newValue == vsb->maximum()) {
        shouldScroll = 10;
        return;
    }
    --shouldScroll;

}


void LogWindow::append(QString str) {
    QTextEdit::append(str);

    if (shouldScroll > 0) {
        QScrollBar* vsb = verticalScrollBar () ;
        vsb->setValue(vsb-> maximum());
        shouldScroll = 10;
    }
}

