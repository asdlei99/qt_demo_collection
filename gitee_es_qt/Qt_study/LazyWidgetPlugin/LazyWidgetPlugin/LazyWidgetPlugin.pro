#-------------------------------------------------
#
# Project created by QtCreator 2018-10-23T20:40:28
#
#-------------------------------------------------

QT       += widgets uiplugin

TARGET = lazywidgetplugin

#DEFINES += MSC

QTDIR_build {
message("enter QTDIR_build:" $${QTDIR_build})
# This is only for the Qt build. Do not use externally. We mean it.
PLUGIN_TYPE = designer
PLUGIN_CLASS_NAME = AnalogClockPlugin
load(qt_plugin)
CONFIG += install_ok
} else {
# Public example:

CONFIG      += plugin
TEMPLATE    = lib

# install
TARGET = $$qtLibraryTarget($$TARGET)
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target
}

include($$PWD/../lazywidgets/DynamicProgressBar/DynamicProgressBar.pri)
include($$PWD/../lazywidgets/ColorProgressBar/ColorProgressBar.pri)

SOURCES += \
    LazyWidgetPlugin.cpp \
    CircleWaitPlugin.cpp \
    ColorProgressBarPlugin.cpp

HEADERS += \
    LazyWidgetPlugin.h \
    CircleWaitPlugin.h \
    ColorProgressBarPlugin.h

DISTFILES += lazywidgetplugin.json

RESOURCES += \
    icons.qrc



