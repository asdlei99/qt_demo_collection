
CONFIG += debug 
# CONFIG -= thread
DEFINES += PROPSCHILDREN_MAIN

INCLUDEPATH += . $$(CPPLIBS)/utils
# INCLUDEPATH += $$(CPPLIBS)/customer 
INCLUDEPATH += $$(CPPLIBS)/dataobjects 

# Input
HEADERS +=  xmlexport.h xmlsupport.h testxmlexport.h customer.h customerlist.h
SOURCES += xmlexport.cpp xmlsupport.cpp testxmlexport.cpp customer.cpp customerlist.cpp main.cpp

#LIBS    += -lcustomer
LIBS    += -ldataobjects
LIBS    += -lutils
LIBS	+= -L$$(CPPLIBS)

# We need this in order to find XML header files.
QT += xml

# place auto-generated files in "invisible" subdirectories
unix {
   UI_DIR = .ui
   MOC_DIR = .moc
   OBJECTS_DIR = .obj
}

