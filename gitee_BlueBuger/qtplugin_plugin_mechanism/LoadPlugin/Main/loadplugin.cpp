#include "loadplugin.h"

#include <QDebug>

LoadPlugin::LoadPlugin(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
        ui.originalLabel->setPixmap( QPixmap( "../Images/source.png" ) );
    connect( ui.filterList, SIGNAL(currentTextChanged(QString)), 
        this, SLOT(filterChanged(QString)) );
    findFilters(); 
    filterChanged( QString() );
}

LoadPlugin::~LoadPlugin()
{

}

void LoadPlugin::findFilters()
{
    QDir path( "./plugins" );
    QStringList subf;
    subf.append("*.dll");
    foreach( QString filename, path.entryList(subf) )
    {
        QPluginLoader loader( path.absoluteFilePath( filename ) );
        qDebug() << loader.metaData();
        QObject *couldBeFilter = loader.instance();
        if( couldBeFilter )
        {            
            FilterInterface *filter = qobject_cast<FilterInterface*>( couldBeFilter );
            if( filter )
            {
                filters[ filter->name() ] = filter;
                ui.filterList->addItem( filter->name() );
            }
        }
    }
}

//////////////////////////////////////////////////////////////////
///slots
void LoadPlugin::filterChanged( QString filter )
{
    if( filter.isEmpty() )
    {
        ui.filteredLabel->setPixmap( *(ui.originalLabel->pixmap() ) );
    }
    else
    {
        QImage filtered = filters[ filter ]->filter( ui.originalLabel->pixmap()->toImage() );
        ui.filteredLabel->setPixmap( QPixmap::fromImage( filtered ) );
    }
}
