#ifndef ECHOPLUGIN_H
#define ECHOPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <EchoInterface.h>


class EchoPlugin : public QObject, EchoInterface
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID EchoInterface_iid FILE "echoplugin.json")
    Q_INTERFACES(EchoInterface)

public:
    QString echo(const QString &message) override;
};

#endif // ECHOPLUGIN_H
