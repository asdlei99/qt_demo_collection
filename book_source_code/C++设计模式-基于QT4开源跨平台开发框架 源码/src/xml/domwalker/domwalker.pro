
QT += xml gui qt3support
CONFIG += console
TEMPLATE = app
INCLUDEPATH += . ..

# Input

SOURCES += main.cpp slacker.cpp domwalker.cpp 
HEADERS += slacker.h domwalker.h 
LIBS += -lutils -ldataobjects -L$$(CPPLIBS)
INCLUDEPATH += . $$(CPPLIBS)/utils $$(CPPLIBS)/dataobjects

unix {
   UI_DIR = .ui
   MOC_DIR = .moc
   OBJECTS_DIR = .obj
}
