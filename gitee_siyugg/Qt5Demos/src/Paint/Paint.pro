#-------------------------------------------------
#
# Project created by QtCreator 2016-09-06T15:28:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
TARGET = Paint
VERSION = 0.0.1
DESTDIR = ../../build/lib
CONFIG += c++11

SOURCES += PaintWindow.cpp \
    PaintArea.cpp

HEADERS  += PaintWindow.h \
    PaintArea.h

FORMS += 
    PaintArea.ui

RESOURCES += \
    image.qrc
