#-------------------------------------------------
#
# Project created by QtCreator 2019-08-09T16:46:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RoomListDemo
TEMPLATE = app


SOURCES += main.cpp\
        roomlistwgt.cpp \
    headwgt.cpp \
    qpixmaphelper.cpp \
    deskwgt.cpp \
    roomwgt.cpp

HEADERS  += roomlistwgt.h \
    headwgt.h \
    qpixmaphelper.h \
    deskwgt.h \
    roomwgt.h

FORMS    += roomlistwgt.ui \
    roomwgt.ui

RESOURCES += \
    myrc.qrc
