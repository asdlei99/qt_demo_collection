include ($$(CPPLIBS)/utils/common.pri)

TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += mymainwindow.h
SOURCES += mainwindow-main.cpp mymainwindow.cpp
