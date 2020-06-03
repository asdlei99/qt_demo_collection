#include "movieview.h"
#include "movietimer.h"
#include <QApplication>

//start id="main"
int main(int argc, char** argv) {
    QApplication app(argc, argv);
    MovieView view;
    MovieTimer movie;  
    app.connect(&movie, SIGNAL(show(const QPixmap*)), 
            &view, SLOT(showPix(const QPixmap*)));
    app.connect(&view, SIGNAL(intervalChanged(int)), 
            &movie, SLOT(setInterval(int)));
    app.connect(&app, SIGNAL(aboutToQuit()), &movie, SLOT(stop()));
    movie.start(); /* Starts the timer, not a thread. */
    view.show();
    return app.exec();
}

//end
