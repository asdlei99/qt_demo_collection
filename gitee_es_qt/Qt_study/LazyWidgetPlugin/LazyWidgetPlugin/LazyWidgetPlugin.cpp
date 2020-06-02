#include "circlewaitplugin.h"
#include "LazyWidgetPlugin.h"
#include "ColorProgressBarPlugin.h"


LazyWidgetPlugin::LazyWidgetPlugin(QObject *parent) :
    QObject(parent)
{
    m_widgets.append(new CircleWaitPlugin(this));
    m_widgets.append(new ColorProgressBarPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> LazyWidgetPlugin::customWidgets() const
{
    return m_widgets;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(LazyWidgetPlugin, LazyWidgetPlugin)
#endif // QT_VERSION < 0x050000
