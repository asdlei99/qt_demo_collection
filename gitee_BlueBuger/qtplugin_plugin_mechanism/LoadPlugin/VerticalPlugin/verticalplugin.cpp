#include "verticalplugin.h"

QString FlipVertically::name() const
{
    return "Vertically";
}

QImage FlipVertically::filter(const QImage &image) const
{    
    QImage result( image.width(), image.height(), image.format() );
    for( int y=0; y<image.height(); ++y )
    {
        for( int x=0; x<image.width(); ++x )
        {   
            result.setPixel(image.width()-1-x,y,image.pixel( x,y));
        }
    }
    return result;
}