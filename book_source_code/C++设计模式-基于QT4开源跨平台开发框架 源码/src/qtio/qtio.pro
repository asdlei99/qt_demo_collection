######################################################################
LIBS	+= -L$$(CPPLIBS)
INCLUDEPATH	+= $$(CPPLIBS)/utils
LIBS 	+=  -lutils
######################################################################

CONFIG += debug console
DEFINES += QT_NOTHREAD_DEBUG

CONFIG -= moc
INCLUDEPATH += .

# Input
SOURCES += qtio-demo.cpp 



