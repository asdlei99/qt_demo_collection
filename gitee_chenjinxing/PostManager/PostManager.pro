#-------------------------------------------------
#
# Project created by QtCreator 2018-06-13T16:33:39
#
#-------------------------------------------------

QT       += core gui
QT +=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PostManager0
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    md5wgt.cpp \
    xjsonrequest.cpp \
    reqbatch.cpp

HEADERS  += mainwindow.h \
    md5wgt.h \
    xjsonrequest.h \
    reqbatch.h \
    reqcrypt.h

FORMS    += mainwindow.ui \
    md5wgt.ui
