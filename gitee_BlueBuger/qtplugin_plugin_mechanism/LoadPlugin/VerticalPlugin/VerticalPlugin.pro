QT += core widgets gui

TEMPLATE = lib
CONFIG += plugin

HEADERS += vertical.h \
           verticalplugin.h

SOURCES += vertical.cpp \
           verticalplugin.cpp

DISTFILES += *.json

DESTDIR = ../Bin/plugins
