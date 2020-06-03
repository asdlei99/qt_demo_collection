TEMPLATE = app
LIBS += -L$$(CPPLIBS)  \ 
        -lutils  \
        -lcards2
INCLUDEPATH += $$(CPPLIBS)/utils  \ 
               $$(CPPLIBS)/cards2

# Input
HEADERS += cardtable.h
SOURCES += boxes.cpp  \ 
           cardtable.cpp
