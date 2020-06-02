QT += core network

QT -= gui

CONFIG += c++11

TARGET = NetClient
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    receiver.cpp \
    receiverservice.cpp \
    tcpsocket.cpp \
    user.cpp \
    userallrcv.cpp \
    userregisterrcv.cpp \
    clientmanager.cpp

HEADERS += \
    public.h \
    receiver.h \
    receiverservice.h \
    tcpsocket.h \
    user.h \
    userallrcv.h \
    userregisterrcv.h \
    clientmanager.h
