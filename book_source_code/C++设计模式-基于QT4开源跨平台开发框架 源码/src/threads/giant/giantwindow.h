#ifndef GIANTWINDOW_H
#define GIANTWINDOW_H
#include <QMainWindow>

class QSlider;
class LogWindow;
class QLabel;
class QPushButton;
class QLineEdit;
class Giant;
class Jack;

/**
  GiantWindow is a very primitive GUI front-end for Giant.
  It has slots which can be hooked up to the giant's signals
  */
//start
class GiantWindow : public QMainWindow {
    Q_OBJECT
  public:
    GiantWindow();
    ~GiantWindow();
  public slots:
    void speakJack();
    void bigText(QString text);
    void smallText(QString text);
    void setDelay(int delayval);
    void terminateThreads();
  private:
    LogWindow *m_GiantLogWindow;
    LogWindow *m_JackLogWindow;
    QLineEdit *m_LineEdit;
    QPushButton *m_SpeakButton, *m_KillButton;
    QSlider *m_GiantSlider;
    Giant* m_Giant;
    Jack* m_Jack;
};
//end
#endif

