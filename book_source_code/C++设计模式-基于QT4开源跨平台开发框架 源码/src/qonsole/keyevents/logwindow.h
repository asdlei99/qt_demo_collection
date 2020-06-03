
#ifndef LOGWINDOW_H
#define LOGWINDOW_H
#include <QTextEdit>

/** An extended QTextEdit suitable for capturing log output.

Each LogWindow is attached to a logger of the same name,
and will monitor messages that go through the named Logger.

Contains a smart scrollbar that won't keep scrolling if you 
are dragging it. 

This class adds an "append" slot to QTextEdit, which also sends
the scrollbar down to the bottom.

see class @ref Logger
*/


class LogWindow : public QTextEdit {
    Q_OBJECT

    public:

    
    /**
       Create a LogWindow (QTextEdit) 
       @param logname - the name of a logger instance to connect to.
       if logname=="debug", then this window monitors qDebug() messages.
          @see Logger
       */
    LogWindow( QString logName = "debug", QWidget* parent=0);
    
    public slots:
    /**
      Start logging all messages that go through a particular
      named logger.
      @param logname - the name of a Logger instance to monitor
         @see Logger
     */         
    void log(QString logname);

    /**
    Extended from the base class to be a slot, and also to
    perform some scrollbar maintenance.
    */
    void append(QString str);

    /**
    Check the position of the scrollbar - if it's at the bottom,
    resume scrolling.
    */
    void checkScroll(int newValue);
    
    private:
    
    int shouldScroll;    

};

#endif        //  #ifndef LOGWINDOW_H

