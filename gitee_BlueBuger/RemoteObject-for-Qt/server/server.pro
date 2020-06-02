QT       += remoteobjects core

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

REPC_SOURCE = ../transfernews.rep

TEMPLATE = app

target.path = $$PWD/server
INSTALLS += target

HEADERS += \
    transfernews.h \
    introduction.h \
    ../struct_def.h

SOURCES += \
    ../struct_def.cpp \
    transfernews.cpp \
    main.cpp

DISTFILES += \
    ../transfernews.rep
