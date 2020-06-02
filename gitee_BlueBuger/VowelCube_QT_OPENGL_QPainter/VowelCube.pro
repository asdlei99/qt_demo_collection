HEADERS += \
    vowelcube.h

SOURCES += \
    vowelcube.cpp \
    main.cpp
QT += opengl core gui widgets

LIBS += -lopengl32

win32 {
    QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
    QMAKE_LFLAGS_CONSOLE = /SUBSYSTEM:CONSOLE,5.01

    DEFINES += _ATL_XP_TARGETING
    QMAKE_CFLAGS += /D_USING_V140_SDK71_
    QMAKE_CXXFLAGS += /D_USING_V140_SDK71_
#此处支持XP
    LIBS += -L$$quote(C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib)
    INCLUDEPATH += $$quote(C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include)
}
