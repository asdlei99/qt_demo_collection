#include "qonsole.h"

#include <logwindow.h>
#include <QDockWidget>
#include <QLineEdit>
#include <QProcess>
#include <QByteArray>
//start id=constructor
Qonsole::Qonsole() {
   m_Logw = new LogWindow("debug"); 
   m_Logw->setReadOnly(true);
   setCentralWidget(m_Logw); 
   m_InputArea = new  QLineEdit(); 
   QDockWidget* qdw = new QDockWidget("Type commands here");
   qdw->setWidget(m_InputArea);
   addDockWidget(Qt::BottomDockWidgetArea, qdw);
   connect (m_InputArea, SIGNAL(returnPressed()), 
            this, SLOT(execute()));
   m_Bash = new QProcess();
   m_Bash->setReadChannelMode(QProcess::MergedChannels); /* Merge
   stdout and stderr. */
   connect (m_Bash, SIGNAL(readyReadStandardOutput()),
             this, SLOT(showOutput()));
   m_Bash->start("bash", QStringList() << "-i"); /* Run bash in
   interactive mode. */ 
}
//end
//start id=methods
void Qonsole::showOutput() { /* A slot that gets called whenever
    input is ready */
    QByteArray bytes = m_Bash->readAllStandardOutput();
    QStringList lines = QString(bytes).split("\n");
    foreach (QString line, lines) {
        m_Logw->append(line);
    }
}

void Qonsole::execute() {
    QString cmdStr = m_InputArea->text() + "\n";
    m_InputArea->setText("");
    m_Logw->append(cmdStr);
    QByteArray bytes = cmdStr.toUtf8(); /* 8-bit Unicode Transformation Format
    */
    m_Bash->write(bytes); /* Send the data into the stdin stream
    of the bash child process */
}
//end
//start id=main
#include <QApplication>

int main(int argc, char* argv[]) {
   QApplication app(argc, argv);
   Qonsole qon;
   qon.show();
   return app.exec();
}
//end

