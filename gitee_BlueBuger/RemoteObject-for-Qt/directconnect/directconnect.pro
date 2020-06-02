QT       += remoteobjects core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = directconnect

REPC_REPLICA = ../transfernews.rep

TEMPLATE = app

target.path = $$PWD/directconnect
INSTALLS += target

HEADERS += \
    directconnect.h \
    mainwindow.h \
    ../struct_def.h

SOURCES += \
    main.cpp \
    directconnect.cpp \
    mainwindow.cpp \
    ../struct_def.cpp

DISTFILES += \
    ../transfernews.rep
