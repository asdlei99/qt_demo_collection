#-------------------------------------------------
#
# Project created by QtCreator 2018-04-09T14:35:44
#
#-------------------------------------------------

QT       += core gui
QT += webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = browerTest
TEMPLATE = app


SOURCES += main.cpp \
    webwidget.cpp \
    webpage.cpp \
    webview.cpp \
    bridge.cpp

HEADERS  += \
    webwidget.h \
    public.h \
    webpage.h \
    webview.h \
    bridge.h
