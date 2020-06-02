QT += quick
CONFIG += c++11

SOURCES += \
        main.cpp \
    PaintedItem.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    PaintedItem.h
