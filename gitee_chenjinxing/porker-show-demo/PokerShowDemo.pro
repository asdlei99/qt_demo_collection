#-------------------------------------------------
#
# Project created by QtCreator 2019-08-09T10:45:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PokerShowDemo
TEMPLATE = app


SOURCES += main.cpp\
        pokershowwgt.cpp \
    card.cpp \
    cardpic.cpp

HEADERS  += pokershowwgt.h \
    card.h \
    cardpic.h

RESOURCES += \
    myrc.qrc
