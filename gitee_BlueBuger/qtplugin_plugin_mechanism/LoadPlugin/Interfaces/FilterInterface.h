#ifndef FILTERINTERFACE_H
#define FILTERINTERFACE_H

#include <QString>
#include <QImage>
#include <QObject>

class FilterInterface
{

public:
    virtual QString name() const=0;
    virtual QImage filter(const QImage &image) const=0;
};

QT_BEGIN_NAMESPACE
    Q_DECLARE_INTERFACE(FilterInterface, "{81AAD42E-1206-443A-8DA2-81C878C23E74}")
    QT_END_NAMESPACE

#endif