CONFIG += console
TEMPLATE = app
INCLUDEPATH += $$(CPPLIBS)/utils
LIBS += -L$$(CPPLIBS) -lutils
# Input
SOURCES += main.cpp
