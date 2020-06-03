TEMPLATE = app
CONFIG -= moc
INCLUDEPATH += .
# Input
HEADERS += sliderlcd.h
SOURCES += sliderlcd.cpp sliderlcd-demo.cpp

QT += gui
CONFIG += debug
LIBS	+= -L$$(CPPLIBS)
INCLUDEPATH	+= $$(CPPLIBS)/utils
LIBS 	+=  -lutils

# place auto-generated files in "invisible" subdirectories
unix {
   UI_DIR = .ui
   MOC_DIR = .moc
   OBJECTS_DIR = .obj
}


