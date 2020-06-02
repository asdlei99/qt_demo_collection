#-------------------------------------------------
#
# Project created by QtCreator 2019-08-20T15:29:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GaitAnalysis
TEMPLATE = app
QMAKE_CXXFLAGS += -Wno-unused-parameter

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        ui/mainwindow.cpp \
    ui/logindialog.cpp \
    connector/connector.cpp \
connector/libusb-test.c \
    ui/footwidget.cpp

HEADERS += \
        ui/mainwindow.h \
    ui/logindialog.h \
    connector/connector.h\
connector/libusb-test.h \
    ui/footwidget.h

INCLUDEPATH = .\
    ui\
connector


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#FORMS += \
#    login2dialog.ui

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/usb/ -llibusb-1.0.dll
LIBS += $$PWD/lib/usb/libusb-1.0.a
#LIBS += $$PWD/lib/usb/libusb-1.0.a

INCLUDEPATH += $$PWD/lib/usb
DEPENDPATH += $$PWD/lib/usb
