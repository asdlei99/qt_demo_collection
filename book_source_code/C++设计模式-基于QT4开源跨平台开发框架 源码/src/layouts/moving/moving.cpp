#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QWidget>
#include <QDebug>
#include "moving.h"
//start id=gridlayout

MovingApp::MovingApp(int argc, char* argv[]) :
    QApplication(argc, argv),
    m_MainWindow(), 
    m_Count(0)  {
                       
    QWidget *center = new QWidget(&m_MainWindow);
    m_MainWindow.setCentralWidget(center); /* The QMainWindow
      takes ownership of this widget, and makes it the central
      widget. We do not need to delete it.  */

    QGridLayout *mainGrid = new QGridLayout;

    m_LeftLayout = new QVBoxLayout;
    m_RightLayout = new QVBoxLayout;

    mainGrid->addLayout(m_LeftLayout, 0,0);
    mainGrid->addLayout(m_RightLayout, 0, 1);    
    QPushButton *moveRight = new QPushButton("Move Right");
    QPushButton *moveLeft = new QPushButton("Move Left");
    mainGrid->addWidget(moveRight, 1,0);
    mainGrid->addWidget(moveLeft, 1,1);
    
    QPushButton *addRight = new QPushButton("Add Right");
    QPushButton *addLeft = new QPushButton("Add Left");

    mainGrid->addWidget(addLeft, 2,0);
    mainGrid->addWidget(addRight, 2,1);
    center->setLayout(mainGrid);
//end
//start id=connections
    connect(moveRight, SIGNAL(pressed()), this, SLOT(moveRight()));
    connect(moveLeft, SIGNAL(pressed()), this, SLOT(moveLeft()));    
    connect(addRight, SIGNAL(pressed()), this, SLOT(newRight()));
    connect(addLeft, SIGNAL(pressed()), this, SLOT(newLeft()));    
    // What do the insertStretch lines do?
    m_LeftLayout->insertStretch(0);
    m_RightLayout->insertStretch(0);
    
    newLeft(); /* puts a label in the left layout */
    newRight();  /* puts a label in the right layout */
    m_MainWindow.move(200,200);
    m_MainWindow.resize(300, 500);
    m_MainWindow.show();
//end
}


QString MovingApp::nextLabel() 
{
    return QString("Item Number %1").arg(m_Count++);
}
void MovingApp::newLeft() 
{
    QLabel* item = new QLabel(nextLabel());
    m_LeftQueue.enqueue(item);
    m_LeftLayout->addWidget(item);
}

void MovingApp::newRight() {
    QLabel* item = new QLabel(nextLabel());
    m_RightLayout->addWidget(item);
    m_RightQueue.enqueue(item);
    
}
//start id=movelayout
void MovingApp::moveLeft() {
    if (m_RightQueue.isEmpty()) return;
    QLabel *top = m_RightQueue.dequeue();
    m_LeftQueue.enqueue(top);
    m_LeftLayout->addWidget(top); /* By adding it to the left, it disappears 
                             from the right */
}

void MovingApp::moveRight() {
    if (m_LeftQueue.isEmpty()) return;
    QLabel *top = m_LeftQueue.dequeue();
    m_RightQueue.enqueue(top);
    m_RightLayout->addWidget(top);
}
//end
int main(int argc, char **argv) {
    MovingApp app(argc, argv);
    return app.exec();
}


