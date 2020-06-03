#include "qonsole.h"

#include <logwindow.h>
#include <QDockWidget>
#include <QLineEdit>
#include <QProcess>
#include <QByteArray>
#include <QEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QTextCursor>


//start id="constructor"
Qonsole::Qonsole() {
   m_Logw = new LogWindow("debug");
   setCentralWidget(m_Logw); 
   m_Logw->installEventFilter(this);
   m_Logw->setLineWrapMode(QTextEdit::WidgetWidth);
   m_Bash = new QProcess();
   m_Bash->setReadChannelMode(QProcess::MergedChannels);
   connect (m_Bash, SIGNAL(readyReadStandardOutput()),
             this, SLOT(showOutput()));
   m_Bash->start("bash", QStringList("-i"), QIODevice::ReadWrite);             
}
//end

//start id="event"
bool Qonsole::eventFilter(QObject *o, QEvent *e) {
    if (e->type() == QEvent::KeyPress) {
        QKeyEvent *k = static_cast<QKeyEvent*> (e); 
        int key = k->key();
        QString str = k->text();
        m_UserInput.append(str);
        updateCursor();
        if ((key == Qt::Key_Return) || (key == Qt::Key_Enter) ) {
            execute();
            return true; /* We processed the event. This
            prevents other widgets from seeing it. */           
        }
        else {
            m_Logw->insertPlainText(str);
            return true;
        }
    }
    return QMainWindow::eventFilter(o, e); /* Let the
          base class eventFilter have a shot at it. */
}
//end    

void Qonsole::showOutput() {
    QByteArray bytes = m_Bash->readAllStandardOutput();
    m_Logw->append(QString(bytes));
}
//start id="update-execute"
void Qonsole::updateCursor() {
    QTextCursor cur = m_Logw->textCursor();
    cur.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    m_Logw->setTextCursor(cur);
}

void Qonsole::execute() {
    QByteArray bytes = m_UserInput.toUtf8();
    m_Bash->write(bytes);
    m_UserInput = "";    
}
//end
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Qonsole qon;
    qon.show();
    return app.exec();
}

