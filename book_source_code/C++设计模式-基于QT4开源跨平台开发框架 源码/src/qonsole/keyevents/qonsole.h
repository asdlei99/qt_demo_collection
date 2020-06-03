#ifndef QONSOLE_H
#define QONSOLE_H

#include <QMainWindow>
class QProcess;
class LogWindow; 
/** Qonsole - konsole without the k
    Example using QProcess and KeyEvents.
    By S. Alan Ezust
*/

//start
class Qonsole : public QMainWindow {
    Q_OBJECT
 public:
    Qonsole();
 public slots:
    void execute();
    void showOutput();
    bool eventFilter(QObject *o, QEvent *e)  ;
 protected:
    void updateCursor();
 private:
    QString m_UserInput;
    LogWindow* m_Logw;
    QProcess* m_Bash;
};
//end
#endif

