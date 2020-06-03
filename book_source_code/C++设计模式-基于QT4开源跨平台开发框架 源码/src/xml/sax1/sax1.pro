LIBS	+= -L$$(CPPLIBS)
LIBS 	+=  -lutils

INCLUDEPATH	+= $$(CPPLIBS)/utils
INCLUDEPATH += .
QT += xml

# Input
HEADERS += myhandler.h
SOURCES += myhandler.cpp tagreader.cpp

