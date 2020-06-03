######################################################################
LIBS	+= -L$$(CPPLIBS) -lutils
INCLUDEPATH	+= $$(CPPLIBS)/utils
######################################################################

TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += codevisitor.h
SOURCES += codevisitor.cpp codevisitor-test.cpp

