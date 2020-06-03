#include <QApplication>
#include <QString>
#include <QLabel>
#include <QWidget>
#include <QDebug>
#include <QTextStream>

int main(int argc, char * argv[]) {
    QApplication myapp(argc, argv);   /* All Qt GUI applications need to create one of these at the start of main(). */
    QWidget wid; /* We are only creating this to see how big it is. */
    qDebug() << "sizeof widget: " << sizeof(wid) 
             << " sizeof qapplication: " << sizeof(myapp) ;
    QString message;
    QTextStream buf(&message); /* This is a stream that allows us to
        "write" to the string, similar usage to std::stringstream. */
    buf << "A QWdget is " << sizeof(wid)
          << " bytes. \nA QObject is " << sizeof(QObject)
          << " bytes. \nA QApplication is " << sizeof(myapp)
          << " bytes.";
    qDebug() << message;   
    QLabel label(message); /* Create a GUI widget with the  message. */
    label.show();    /* Make the label visible. */
    return myapp.exec(); /* Enter the event loop, and wait for
        the user to do something. When the user exits, 
        so does myapp.exec(). */
};

