#ifndef QPIXMAPHELPER_H
#define QPIXMAPHELPER_H

#include <QPixmap>

class QPixmapHelper
{
public:
    QPixmapHelper();

    static QPixmap PixmapToRound(QPixmap &src, int radius);
    static QPixmap PixmapToTriangle(QPixmap &src, int side);


};

#endif // QPIXMAPHELPER_H
