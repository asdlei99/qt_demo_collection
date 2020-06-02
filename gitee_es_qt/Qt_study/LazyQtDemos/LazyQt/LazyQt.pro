#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T15:40:29
#
#-------------------------------------------------

QT       += core gui axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11 c++14

TARGET = LazyQt
TEMPLATE = app

include($$PWD/../common/common.pri)
include($$PWD/../views/views.pri)

SOURCES += \
        main.cpp \
        MainWindow.cpp

HEADERS += \
        MainWindow.h

FORMS += \
        MainWindow.ui
