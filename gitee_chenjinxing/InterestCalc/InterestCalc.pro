#-------------------------------------------------
#
# Project created by QtCreator 2018-05-21T09:26:53
#
#-------------------------------------------------

QT       += core gui
QT +=axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InterestCalc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xexcel.cpp

HEADERS  += mainwindow.h \
    xexcel.h

FORMS    += mainwindow.ui
