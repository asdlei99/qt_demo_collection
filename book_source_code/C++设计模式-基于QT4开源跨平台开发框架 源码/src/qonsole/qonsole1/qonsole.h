#ifndef QONSOLE_H
#define QONSOLE_H

class LogWindow; 

#include <QMainWindow>
class QLineEdit;
class QProcess;

/**
  A simple demo application that shows how to use QProcess,
  with signals/slots providing bidirectional communication.
  */

class Qonsole : public QMainWindow {
    Q_OBJECT
    public:
    Qonsole();

    public slots:
    void execute();
    void showOutput();
    
    private:
    LogWindow* m_Logw;
    QLineEdit* m_InputArea;
    QProcess* m_Bash;
};

#endif

