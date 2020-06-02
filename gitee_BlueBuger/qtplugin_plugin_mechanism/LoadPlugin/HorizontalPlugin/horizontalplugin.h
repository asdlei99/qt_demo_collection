#include "../Interfaces/FilterInterface.h"

class FlipHorizontally:public QObject,FilterInterface
{
    Q_OBJECT
        Q_PLUGIN_METADATA(IID "{6A5B6FCE-94D2-40CB-824C-34EEA2FA7367}" FILE "horizontalplugin.json")
        Q_INTERFACES(FilterInterface)
public:
    QString name() const;
    QImage filter(const QImage &image) const;
};