#include "myhandler.h"
#include <QFile>
#include <QXmlInputSource>
#include <QXmlSimpleReader>
#include <QDebug>

int main( int argc, char **argv ) {
    if ( argc < 2 ) {
        qDebug() << QString("Usage: %1 <xmlfile>").arg(argv[0]);
        return 1;
    }
    for ( int i=1; i < argc; ++i ) {
        QFile xmlFile( argv[i] );
        QXmlInputSource source( &xmlFile );
        MyHandler handler; 
        QXmlSimpleReader reader; /* the generic parser */
        reader.setContentHandler( &handler );  /* Hook up
           the objects together. */
        reader.parse( source );   /* Start parsing. */
    }
    return 0;
}
