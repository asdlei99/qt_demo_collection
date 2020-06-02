#ifndef ECHOINTERFACE_H
#define ECHOINTERFACE_H

#include <QString>

class EchoInterface
{
public:
    virtual ~EchoInterface() {}
    virtual QString echo(const QString &message) = 0;
};

QT_BEGIN_NAMESPACE
#define EchoInterface_iid "com.lazy.Qt.study.EchoInterface"

Q_DECLARE_INTERFACE(EchoInterface, EchoInterface_iid)
QT_END_NAMESPACE

#endif // ECHOINTERFACE_H
