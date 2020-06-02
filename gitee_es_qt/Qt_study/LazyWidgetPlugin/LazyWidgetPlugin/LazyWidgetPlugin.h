#ifndef LAZYWIDGETPLUGIN_H
#define LAZYWIDGETPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetCollectionInterface>


class LazyWidgetPlugin : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "com.lazy.Qt.QDesignerLazyWidgetCollectionInterface" FILE "LazyWidgetPlugin.json")
#endif // QT_VERSION >= 0x050000

public:
    explicit LazyWidgetPlugin(QObject *parent = 0);

    virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
    QList<QDesignerCustomWidgetInterface*> m_widgets;
};

#endif // LAZYWIDGETPLUGIN_H
