TEMPLATE = app
QT += gui
CONFIG += debug

LIBS +=  -ldataobjects  -lfiletagger -lutils  -L$$(CPPLIBS)

INCLUDEPATH  += $$(CPPLIBS)/dataobjects  \
                $$(CPPLIBS)/filetagger  \
                $$(CPPLIBS)/utils

HEADERS += propertyselectormodel.h \
           propertyselectorview.h  \
           propertyselectorcontrol.h
           
SOURCES += propertyselectormodel.cpp \
           propertyselectorview.cpp \
           propertyselectorcontrol.cpp

           
