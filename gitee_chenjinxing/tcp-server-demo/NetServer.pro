QT += core network sql
QT -= gui

CONFIG += c++11

TARGET = NetServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    tcpserver.cpp \
    tcpsocket.cpp \
    receiver.cpp \
    userregisterrcv.cpp \
    receiverservice.cpp \
    servermanager.cpp \
    database.cpp \
    user.cpp \
    userservice.cpp \
    userallrcv.cpp \
    serverthread.cpp

HEADERS += \
    tcpserver.h \
    tcpsocket.h \
    receiver.h \
    userregisterrcv.h \
    public.h \
    receiverservice.h \
    servermanager.h \
    database.h \
    user.h \
    userservice.h \
    userallrcv.h \
    serverthread.h
