#-------------------------------------------------
#
# Project created by QtCreator 2016-06-13T17:23:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt5DemosDlg
TEMPLATE = app
DESTDIR = ../../build/bin
CONFIG += c++11
QMAKE_RPATHDIR += ../../build/lib
QMAKE_LFLAGS += -Wl,--rpath=../lib
SOURCES += main.cpp \
    Qt5DemosDlg.cpp

HEADERS  += \
    ../QtStdDlgs/InforDialog.h \
    ../QtStdDlgs/InputDialog.h \
    ../QtStdDlgs/QtStdDialogs.h \
	../QtProgressBar/ProgressBar.h\
	../QtClock/QtClock.h\
	../QtExtDlg/QtExtDlg.h\
	../QtGeometryDlg/QtGeometryDlg.h\
	../QtImageView/QtImageView.h\
	../QtPalette/QtPaletteDlg.h\
	../QtShapeWidget/QtShapeWidget.h\
	../QtSplashWindow/QtSplashWindow.h\
	../QtWordProcessor/QtWordProcessor.h\
	../GraphicsItems/MainWindow.h\
	Qt5DemosDlg.h

FORMS    += \  
    Qt5DemosDlg.ui

LIBS += -L../../build/lib -lQtStdDlgs -lQtProgressBar -lQtClock -lQtExtDlg -lQtGeometryDlg -lQtImageView -lQtMainWindow -lQtPalette -lQtProgressBar -lQtShapeWidget -lQtSplashWindow -lQtStdDlgs -lGraphicsItems

RURCES += \
    icon.qrc
