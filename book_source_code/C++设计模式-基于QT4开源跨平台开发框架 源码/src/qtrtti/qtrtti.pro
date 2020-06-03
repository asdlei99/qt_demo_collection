######################################################################
LIBS	+= -L$$(CPPLIBS) -lutils
INCLUDEPATH	+= $$(CPPLIBS)/utils
######################################################################

TEMPLATE = app
INCLUDEPATH += .

# Input
SOURCES += qtrtti.cpp
