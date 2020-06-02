QT += core widgets gui

TEMPLATE = lib
CONFIG += plugin

HEADERS += horizontal.h \
           horizontalplugin.h

SOURCES += horizontal.cpp \
           horizontalplugin.cpp

DISTFILES += *.json

DESTDIR = ../Bin/plugins
