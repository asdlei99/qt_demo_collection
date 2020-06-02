#-------------------------------------------------
#
# Project created by QtCreator 2016-09-17T08:22:56
#
#-------------------------------------------------



TARGET = Draw
TEMPLATE = lib 
VERSION = 0.0.1
DESTDIR = ../../build/lib
INCLUDEPATH += .
CONFIG += qt
QT       += core gui widgets

SOURCES += DrawWindow.cpp \
    DrawArea.cpp

HEADERS  += DrawWindow.h \
    DrawArea.h

FORMS    += DrawWindow.ui

RESOURCES += icon.qrc
