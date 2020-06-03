#include "movieview.h"
#include "moviethread.h"
#include <QApplication>

//start id="main"
int main(int argc, char** argv) {
    QApplication app(argc, argv);
    MovieView view;
    MovieThread movie;  
    app.connect(&movie, SIGNAL(show(const QPixmap*)), 
            &view, SLOT(showPix(const QPixmap*)));
    app.connect(&view, SIGNAL(intervalChanged(int)), 
            &movie, SLOT(setInterval(int)));
    app.connect(&app, SIGNAL(aboutToQuit()), &movie, SLOT(stop()));
    movie.start(); /* A new thread starts executing at this
    point, but the method returns immediately. The new thread
    starts by calling movie.run(). */
    view.show();
    return app.exec();
}

//end
