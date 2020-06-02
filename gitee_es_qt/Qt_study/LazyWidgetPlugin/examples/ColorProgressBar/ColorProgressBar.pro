#-------------------------------------------------
#
# Project created by QtCreator 2018-10-24T10:33:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ColorProgressBar
TEMPLATE = app

include($$PWD/../../lazywidgets/ColorProgressBar/ColorProgressBar.pri)

SOURCES += \
        main.cpp \
        ColorProgressBarTest.cpp

HEADERS += \
        ColorProgressBarTest.h

FORMS += \
        ColorProgressBarTest.ui
