#-------------------------------------------------
#
# Project created by QtCreator 2017-01-11T13:48:38
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pdfdemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


HEADERS += \
    src/abstractinfodock.h \
    src/documentobserver.h \
    src/embeddedfiles.h \
    src/fonts.h \
    src/info.h \
    src/mainwindow.h \
    src/metadata.h \
    src/navigationtoolbar.h \
    src/optcontent.h \
    src/pageview.h \
    src/permissions.h \
    src/thumbnails.h \
    src/toc.h \
    src/viewer.h

SOURCES += \
    src/abstractinfodock.cpp \
    src/documentobserver.cpp \
    src/embeddedfiles.cpp \
    src/fonts.cpp \
    src/info.cpp \
    src/main_viewer.cpp \
    src/mainwindow.cpp \
    src/metadata.cpp \
    src/navigationtoolbar.cpp \
    src/optcontent.cpp \
    src/pageview.cpp \
    src/permissions.cpp \
    src/thumbnails.cpp \
    src/toc.cpp \
    src/viewer.cpp



win32: LIBS += -L$$PWD/libs/lib/ -llibpoppler.dll -llibpoppler-qt5.dll
unix:!macx: LIBS += -L$$PWD/libs/lib/ -lpoppler -lpoppler-qt5

INCLUDEPATH += $$PWD/libs/include
DEPENDPATH += $$PWD/libs/include


