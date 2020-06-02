QT -= gui
QT += core

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32{
#    system(copy /y $$PWD//data.json $$OUT_PWD)
#    copy_cmd = xcopy $$PWD/data.json $$OUT_PWD
#    system('xcopy $$PWD/data.json $$OUT_PWD /Y')


#    system($$quote($$copy_cmd))
#system($$copy_cmd)
#    system("copy /Y $$PWD\\data.json $$OUT_PWD\\data.json")
#    $$QMAKE_COPY $$copy_cmld
#    $(COPY_FILE) $$PWD/data.json $$OUT_PWD

# $(COPY_DIR) $SOURCEOFFILE $$OUT_PWD/newFolder
# system($$COPY_FILE $$PWD/data.json $$OUT_PWD)
}

message(--------------------------------)
message(PWD $$PWD)
message(OUT_PWD $$OUT_PWD)
message(xcopy: $$copy_cmd)
message(QMAKE_COPY: $$QMAKE_COPY)
message(cmd:$$PWD/data.json $$OUT_PWD)
message(COPY_FILE:$$COPY_FILE)
message(--------------------------------)
