include ($$(CPPLIBS)/utils/common.pri)

TEMPLATE = app
INCLUDEPATH += .
QT += gui
# Input
HEADERS += movieview.h \
           moviethread.h  
#           movietimer.h

SOURCES += moviethread.cpp movieview.cpp moviethreadmain.cpp
#movietimer.cpp

# For locating the files.
RESOURCES = animate.qrc
