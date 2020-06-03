include ($$(CPPLIBS)/utils/common.pri)
TEMPLATE = app
QT += sql
DEPENDPATH += .
INCLUDEPATH += .

LIBS += -lid3 -lutils -ldataobjects -lfiletagger -lforms -lmysqlclient -L$$(CPPLIBS)
INCLUDEPATH += . $$(CPPLIBS)/utils $$(CPPLIBS)/forms $$(CPPLIBS)/dataobjects $$(CPPLIBS)/filetagger


# Input
HEADERS +=  dbviewapp.h
SOURCES +=  dbviewapp.cpp

