
include ($$(CPPLIBS)/utils/common.pri)
TEMPLATE = app
INCLUDEPATH += .

# Input
HEADERS += giant.h giantwindow.h jack.h
SOURCES += giant.cpp giantwindow.cpp jack.cpp

QT += gui


