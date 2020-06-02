#include <CircleWait.h>
#include "CircleWaitPlugin.h"

CircleWaitPlugin::CircleWaitPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void CircleWaitPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CircleWaitPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CircleWaitPlugin::createWidget(QWidget *parent)
{
    return new CircleWait(parent);
}

QString CircleWaitPlugin::name() const
{
    return QStringLiteral("CircleWait");
}

QString CircleWaitPlugin::group() const
{
    return QStringLiteral("LazyWidget");
}

QIcon CircleWaitPlugin::icon() const
{
    return QIcon(":/images/CircleWait.png");
}

QString CircleWaitPlugin::toolTip() const
{
    return QString();
}


QString CircleWaitPlugin::whatsThis() const
{
    return QString();
}

bool CircleWaitPlugin::isContainer() const
{
    return false;
}


QString CircleWaitPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
         " <widget class=\"CircleWait\" name=\"circleWait\">\n"
         "  <property name=\"geometry\">\n"
         "   <rect>\n"
         "    <x>0</x>\n"
         "    <y>0</y>\n"
         "    <width>100</width>\n"
         "    <height>100</height>\n"
         "   </rect>\n"
         "  </property>\n"
         " </widget>\n"
         "</ui>";
}

QString CircleWaitPlugin::includeFile() const
{
    return QStringLiteral("CircleWait.h");
}

