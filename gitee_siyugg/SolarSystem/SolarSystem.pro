#-------------------------------------------------
#
# Project created by QtCreator 2016-10-03T15:18:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SolarSystem
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        SolorSystemWin.cpp \
    Orbit.cpp \
    Planet.cpp

HEADERS  += SolorSystemWin.h \
    Orbit.h \
    Planet.h

FORMS    += SolorSystemWin.ui

RESOURCES += \
    planets.qrc
