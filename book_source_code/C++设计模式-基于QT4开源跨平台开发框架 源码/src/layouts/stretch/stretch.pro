include ($$(CPPLIBS)/utils/common.pri)

TEMPLATE = app
LIBS += -lcards
INCLUDEPATH += $$(CPPLIBS)/cards

# Input
HEADERS += cardtable.h
SOURCES += stretch.cpp cardtable.cpp
