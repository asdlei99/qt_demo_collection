//start
#include "dialogs.h"
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QAction>
#include <QDebug>
#include <QApplication>

Dialogs::Dialogs() {
    QWidget::setWindowTitle( "Gullap Poll" ); /* The ClassName:: prefixes we use in methods here are not necessary, 
because the methods can be called on "this".
We list the classname only to show the human reader
which class the method was inherited from. */
    QWidget::move(300, 300);
//end
//start id="menu"    
    /* Insert a menu into the menubar. */
    QMenu *menu = new QMenu("&Questions", this);

    QMainWindow::menuBar()->addMenu(menu);
    
    /* Add some choices to the menu. */
    menu->addAction("&Ask question",
                    this, SLOT(askQuestion()), tr("Alt+A"));
    menu->addAction("Ask a &dumb question",
                    this, SLOT(askDumbQuestion()), tr("Alt+D"));
}
//end
//start id="messagebox"
void Dialogs::askQuestion() {
    bool done=false;
    QString q1("Who was Canadian Prime Minister in 1847?"),
            a0("John A. Macdonald"), a1("Alexander Mackenzie"),
            a2("Sir Wilfred Laurier");
    while (!done) {
        int ans = QMessageBox::
                  question( this, /* Message box is modal relative to its parent. */
                  "Difficult Question",
                  q1, a0, a1, a2, 
                  0,  /* default value */
                  -1  /* value sent on "esc" or "windowclose" */ ) ;
        if (ans < 0) return; /* If window was closed, no QButton was pressed. */                                       
        switch( ans ) {
        case 0:
            answer = a0;
            break;
        case 1:
            answer = a1;
            break;
        case 2:
            answer = a2;
            break;
        }
        QString q2(QString("Your answer was: %1."
                           " That is incorrect.\n Try again?")
                           .arg(answer));
        int again = QMessageBox::
                    question(this, "Your Score", q2,
                    "No", "Yes", "I give up - what's the answer?");
                                          
        if ( again <1 ) {
            return;
        }
        if (again == 2) {
            QMessageBox::
            information(this, "Ha Ha!",
                        "There was no prime minister until 1867",
                        "Grrrrr.....");
            return;
        }
    }
}

//end

void Dialogs::askDumbQuestion() {

    switch( QMessageBox::
            question( this, "Stupid Question",
                     "What kind of political animal are you?",
                     "donkey", "elephant","penguin",
                     1, -1 ) ) {
    case 0:
        answer = "<i>Ya gotta love national health care!</i>";
        QMessageBox::
        information(this, "Useless Information", answer,
                    QMessageBox::Ignore, QMessageBox::Ok,
                    QMessageBox::NoButton);
        return;
        break;
    case 1:
        answer = "Down with evolution!";
        QMessageBox::
        warning(this, "What did science ever do for me?", answer,
                QMessageBox::Ignore, QMessageBox::Cancel, 
                QMessageBox::YesAll);

        return;
        break;
    case 2:
        answer = "<b>Go Linux!!</b>!";
        QMessageBox::
        critical(this, "critical message", answer, 
                 QMessageBox::Abort, QMessageBox::Retry, 
                 QMessageBox::Ignore);
        return;
        break;
    }
}

//start

int main( int argc, char ** argv ) {
    QApplication a( argc, argv );
    Dialogs *awd = new Dialogs();
    awd->show();
    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
    return a.exec();
}

