#include <QLineEdit>
#include <QSlider>
#include <QPushButton>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QApplication>
#include <QSplitter>

#include <logwindow.h>
#include <logger.h>

#include "giantwindow.h"
#include "giant.h"
#include "jack.h"

//start
GiantWindow::GiantWindow() {
    resize(800, 600);
    m_Giant = new Giant();
    m_Jack = new Jack();
    /* The giant talks to the GiantWindow through signals and slots */    
    connect (m_Giant, SIGNAL(say(QString)), this, SLOT(bigText(QString)));
    connect (m_Giant, SIGNAL(small(QString)), this, SLOT(smallText(QString)));
    connect (m_Jack,  SIGNAL(chopBeanstalk()), m_Giant, SLOT(die()));    
    connect (m_Giant, SIGNAL(giantDead()), this, SLOT(terminateThreads()));
    
    m_GiantLogWindow = new LogWindow("giant");
    m_GiantLogWindow->setToolTip("This is what the giant says");

    m_JackLogWindow = new LogWindow("jack"); /* A LogWindow
         will display all messages sent to the logger of the
         same name. In this case, Logger::getLogger("jack")
         will return an object through which you send messages
         that get displayed in this window */
    m_JackLogWindow->setToolTip("This is what Jack is doing");
    Logger *jackLog = Logger::getLogger("jack");

    connect (jackLog, SIGNAL(data(const QString&)),
             m_Giant, SLOT(hear(const QString&))); /* The giant
             can hear what jack is saying!! */ 
    QSplitter *split = new QSplitter(this); /* split-window 
         container with draggable splitter between two widgets */
    split->addWidget(m_GiantLogWindow);
    split->addWidget(m_JackLogWindow); /* We can only add two
       widgets to split. */
    setCentralWidget(split);
//end
    m_LineEdit = new QLineEdit("I'm in your house, giant!");
    m_LineEdit->setToolTip("What does Jack say?");
    connect (m_LineEdit, SIGNAL(returnPressed()), this, SLOT(speakJack()));

    m_SpeakButton = new QPushButton("say something");
    m_KillButton = new QPushButton("kill the giant");
    connect (m_KillButton, SIGNAL(clicked()), m_Jack, SLOT(killGiant()));
    connect (m_SpeakButton, SIGNAL(clicked()), this, SLOT(speakJack()));    

    QDockWidget* qdw = new QDockWidget("Jack says:");
    QWidget *bottomArea = new QWidget();
    QHBoxLayout* bottomLayout = new QHBoxLayout(bottomArea);
    bottomLayout->addWidget(m_LineEdit);
    bottomLayout->addWidget(m_SpeakButton);
    bottomLayout->addWidget(m_KillButton);    
    qdw->setWidget(bottomArea);
    addDockWidget(Qt::BottomDockWidgetArea, qdw);
    // set up delay slider
    m_GiantSlider = new QSlider(Qt::Vertical);
    m_GiantSlider->setRange(0, 3000);
    m_GiantSlider->setTickInterval(200);
    m_GiantSlider->setValue(1000);
    m_GiantSlider->setToolTip("How slow is the giant?");
    connect(m_GiantSlider, SIGNAL(valueChanged(int)), this, SLOT(setDelay(int)));
    qdw = new QDockWidget();
    qdw->setWidget(m_GiantSlider);
    addDockWidget(Qt::LeftDockWidgetArea, qdw);
    m_Giant->start();
    m_Jack->start();
}


int main(int argc, char** argv) {
    QApplication app(argc, argv);
    GiantWindow gw;
    gw.show();
    return app.exec();
}


void GiantWindow::speakJack() {
   QString str = m_LineEdit->text();
   Logger *log = Logger::getLogger("jack");
   log->info(str);
}

void GiantWindow::setDelay(int newValue) {
    m_Giant->setDelay(newValue);
    m_Jack->setDelay(newValue);
    QString str;
    
    str = QString("delay=%1").arg(newValue);
    m_GiantSlider->setToolTip(str);
}

void GiantWindow::bigText(QString text) {
    m_GiantLogWindow->setFontPointSize(16);
    m_GiantLogWindow->append(text);
}

void GiantWindow::smallText(QString text) {
    m_GiantLogWindow->setFontPointSize(9);
    m_GiantLogWindow->append(text);
}

GiantWindow::~GiantWindow() {
   delete m_Giant;   
    
}

void GiantWindow::terminateThreads() {
    m_Giant->terminate();
    m_Jack->terminate();
    m_SpeakButton->disconnect();
}


