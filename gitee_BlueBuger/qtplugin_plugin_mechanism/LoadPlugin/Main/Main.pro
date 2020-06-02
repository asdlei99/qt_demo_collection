QT += core widgets gui

TEMPLATE = app

HEADERS += loadplugin.h

SOURCES += loadplugin.cpp \
           main.cpp

DISTFILES += *.json

RESOURCES += \
    loadplugin.qrc

FORMS += \
    loadplugin.ui

DESTDIR = ../Bin
