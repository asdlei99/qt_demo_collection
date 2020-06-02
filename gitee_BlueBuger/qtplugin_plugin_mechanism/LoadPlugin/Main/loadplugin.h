#ifndef LOADPLUGIN_H
#define LOADPLUGIN_H

#include <QtWidgets/QMainWindow>
#include <QMap>
#include <QString>
#include <QDir>
#include <QPluginLoader>
#include "../Interfaces/FilterInterface.h"
#include "ui_loadplugin.h"

class LoadPlugin : public QMainWindow
{
    Q_OBJECT

public:
    LoadPlugin(QWidget *parent = 0);
    ~LoadPlugin();
    private slots:
        void filterChanged( QString );
private:
    Ui::LoadPluginClass ui;

    void findFilters();
    QMap<QString, FilterInterface*> filters;
};

#endif // LOADPLUGIN_H
