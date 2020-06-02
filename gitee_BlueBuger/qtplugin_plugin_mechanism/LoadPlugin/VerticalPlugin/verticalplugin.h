#include "../Interfaces/FilterInterface.h"

class FlipVertically:public QObject,FilterInterface
{
    Q_OBJECT
        Q_PLUGIN_METADATA(IID "{52D000C5-108A-4A00-B109-8C5509BD8F38}" FILE "verticalplugin.json")
        Q_INTERFACES(FilterInterface)
public:
    QString name() const;
    QImage filter(const QImage &image) const;
};