#-------------------------------------------------
#
# Project created by QtCreator 2018-10-12T15:34:25
#
#-------------------------------------------------
TEMPLATE = lib
CONFIG += plugin
QT       += widgets

# 包含接口定义文件
INCLUDEPATH  += $$PWD/../include

TARGET = echoplugin

# message("QT_LAZY_SRCDIR=$$(QT_LAZY_SRCDIR)")

DESTDIR         = $$(QT_LAZY_SRCDIR)/build_msvc2015/echoplugin
#DESTDIR = $$[QT_INSTALL_PLUGINS]/styles
#message("DESTDIR=$$DESTDIR")
#message($$[QT_INSTALL_PLUGINS])


SOURCES += \
        echoplugin.cpp

HEADERS += \
        echoplugin.h \

DISTFILES += echoplugin.json 

unix {
    target.path = /usr/lib
    INSTALLS += target
}
