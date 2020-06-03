#ifndef MOVIETIMER_H
#define MOVIETIMER_H

#include <QTimer>
#include <QQueue>
#include <QVector>
#include <QPixmap>
#include "movie.h"

/**
   An example class which makes use of QThread and QPixMap.
   In order to display this movie, you must connect the
   show(QPixMap*) signal to an appropriate slot that shows it.
*/
//start
class MovieTimer :public QTimer {
    Q_OBJECT
 public:
    MovieTimer();
    ~MovieTimer();
    void loadPics();
 public slots:
    void nextFrame();
    void addFile(const QString& filename);
    void setInterval(int newDelay); 
 signals:
    void show(const QPixmap *image);
 private:
    QVector<QPixmap> pics;
    int current;
};
//end

#endif

