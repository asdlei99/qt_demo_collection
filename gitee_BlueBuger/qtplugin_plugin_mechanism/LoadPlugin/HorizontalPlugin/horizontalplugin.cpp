#include "horizontalplugin.h"

QString FlipHorizontally::name() const
{
    return "Horizontally";
}

QImage FlipHorizontally::filter(const QImage &image) const
{
    QImage result( image.width(), image.height(), image.format() );   
    for( int y=0; y<image.height(); ++y )
    {
        for( int x=0; x<image.width(); ++x )
        {
            result.setPixel( x, image.height()-1-y, image.pixel( x, y ) );
        }
    }
    return result;
}