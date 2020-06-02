# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = QtCamera
DESTDIR = ./
QT += core gui
CONFIG += release
DEFINES +=
INCLUDEPATH += ./GeneratedFiles \
    ./GeneratedFiles/Release \
    . \
    $(OPENCV_INC_PATH)
LIBS += -L"$(OPENCV_LIB_PATH)" \
    -lopencv_core \
    -lopencv_video \
    -lopencv_highgui \
    -lopencv_imgproc
PRECOMPILED_HEADER = StdAfx.h
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/release
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(QtCamera.pri)
