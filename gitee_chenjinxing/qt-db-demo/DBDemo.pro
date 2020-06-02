#-------------------------------------------------
#
# Project created by QtCreator 2019-08-12T12:38:04
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DBDemo
TEMPLATE = app


SOURCES += main.cpp\
        dbwgt.cpp \
    user.cpp \
    database.cpp \
    userservice.cpp

HEADERS  += dbwgt.h \
    user.h \
    database.h \
    userservice.h

FORMS    += dbwgt.ui
