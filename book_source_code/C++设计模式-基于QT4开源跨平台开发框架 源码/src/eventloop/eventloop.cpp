//start id=setgui
#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QDebug>
#include "messager.h"

/** First interactive GUI application
    Uses buttons, signals and slots.
*/

QWidget* setGui(QWidget *box) {
    QLayout* layout = new QVBoxLayout;
    box->setLayout(layout); /* box is the parent of layout. */


    QTextEdit *te = new QTextEdit; /* window for qDebug messages */
    layout->addWidget(te); /* add as grandchild to box */

    te->setHtml("Some <b>text</b> in the <tt>QTextEdit</tt>"
        "edit window <i>please</i>?");

    QPushButton *quitButton=new QPushButton("Quit");
    layout->addWidget(quitButton);

    QPushButton *shoutButton = new QPushButton("Shout");
    layout->addWidget(shoutButton);

    Messager *msgr = new Messager("This dialog will self-destruct.", box);


    QObject::connect(quitButton, SIGNAL(clicked()),
                  qApp, SLOT(quit())); /* qApp is a global variable that
                  points to the current QApplication object. */

    qApp->connect(shoutButton, SIGNAL(clicked()), msgr, SLOT(shout()));
    return box;
}
//end

//start id=main
int main(int argc, char * argv[]) {
    QApplication myapp(argc, argv); /* Every GUI, multithreaded,
                   or event-driven Qt Application must have
                   a QApplication object defined at the top
                   of main(). */

    QWidget rootWidget;
    setGui(&rootWidget);

    rootWidget.show();  /* Show the widget on the screen. */
    return myapp.exec();  /* Enter an event loop. */
};
//end

