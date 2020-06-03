include ($$(CPPLIBS)/utils/commmon.pri)

LIBS += -lcustomer -ldataobjects -lutils -L$$(CPPLIBS)
INCLUDEPATH += $$(CPPLIBS)/customer $$(CPPLIBS)/dataobjects $$(CPPLIBS)/utils

TEMPLATE = app
TARGET += 
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += debug gui

# Input
SOURCES += tablemodel.cpp


