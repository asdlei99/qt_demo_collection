#-------------------------------------------------
#
# Project created by QtCreator 2016-06-03T09:56:02
#
#-------------------------------------------------

QT       += core gui network sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = qt_open_icon
TEMPLATE = app

INCLUDEPATH += font core utils common \
utils/label utils/button utils/animation utils/dialog utils/timeset \
utils/wheel utils/navbar utils/table utils/qcustomplot\
utils/desktop utils/desktop/procedure \
utils/digitalinput\
service service/database service/database/connectionpool service/database/dao service/database/entity

win32:msvc{
    CONFIG +=c++11
}else{
    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_CXXFLAGS += -Wunused-function
    QMAKE_CXXFLAGS += -Wunused-parameter
    QMAKE_CXXFLAGS += -Wreorder
    QMAKE_CXXFLAGS += -Wswitch
}

SOURCES += main.cpp\
    core/iconhelper.cpp \
    font/abstractfont.cpp \
    font/fontawesomewebfont.cpp \
    font/muifont.cpp \
    utils/button/basebutton.cpp \
    utils/button/buttontest.cpp \
    utils/button/switchbutton.cpp \
    utils/button/loopbutton.cpp \
    utils/button/batterybutton.cpp \
    utils/animation/abstractanimation.cpp \
    utils/animation/animationcenter.cpp \
    utils/animation/animationcover.cpp \
    utils/animation/animationfly.cpp \
    utils/animation/animationsharp.cpp \
    utils/animation/animationslide.cpp \
    utils/animation/animationtest.cpp \
    utils/animation/animationwidget.cpp \
    utils/dialog/toast.cpp \
    utils/dialog/dialogtest.cpp \
    utils/label/baselabel.cpp \
    font/timefont.cpp \
    utils/qcustomplot/qcustomplot.cpp \
    utils/navbar/navbar.cpp \
    utils/dialog/basemessagebox.cpp \
    common/utilscommon.cpp \
    utils/desktop/desktop.cpp \
    utils/desktop/procedure/qqprocedure.cpp \
    utils/desktop/procedure/procedure.cpp \
    service/database/connectionpool/connectionpool.cpp \
    service/database/dao/abstractdao.cpp \
    service/database/dao/studentdaoimpl.cpp \
    service/database/entity/studentdata.cpp \
    service/database/databasetest.cpp \
    utils/qcustomplot/customplottest.cpp \
    utils/table/baselist.cpp \
    utils/table/listtest.cpp \
    utils/table/normallist.cpp \
    utils/table/linedelegate.cpp \
    utils/table/navlist.cpp \
    utils/navbar/navbartest.cpp \
    utils/digitalinput/digitalinput.cpp \
    utils/digitalinput/digitalinputtest.cpp \
    utils/button/groupbutton.cpp \
    test/colortest.cpp \
    common/global.cpp

HEADERS  += \
    core/iconhelper.h \
    font/abstractfont.h \
    font/fontawesomewebfont.h \
    font/muifont.h \
    font/fonts.h \
    utils/button/basebutton.h \
    utils/button/buttontest.h \
    utils/button/switchbutton.h \
    utils/button/loopbutton.h \
    utils/button/batterybutton.h \
    utils/animation/abstractanimation.h \
    utils/animation/animation.h \
    utils/animation/animationcenter.h \
    utils/animation/animationcover.h \
    utils/animation/animationfly.h \
    utils/animation/animationsharp.h \
    utils/animation/animationslide.h \
    utils/animation/animationtest.h \
    utils/animation/animationwidget.h \
    utils/dialog/toast.h \
    utils/dialog/dialogtest.h \
    utils/label/baselabel.h \
    font/timefont.h \
    utils/qcustomplot/qcustomplot.h \
    utils/navbar/navbar.h \
    utils/dialog/basemessagebox.h \
    common/utilscommon.h \
    utils/desktop/desktop.h \
    utils/desktop/procedure/qqprocedure.h \
    utils/desktop/procedure/procedure.h \
    utils/desktop/desktopcmd.h \
    utils/desktop/procedure/procedurehead.h \
    service/database/connectionpool/connectionpool.h \
    service/database/dao/abstractdao.h \
    service/database/dao/studentdaoimpl.h \
    service/database/entity/studentdata.h \
    service/database/databasetest.h \
    utils/qcustomplot/customplottest.h \
    utils/table/baselist.h \
    utils/table/listtest.h \
    utils/table/normallist.h \
    utils/table/linedelegate.h \
    utils/table/navlist.h \
    utils/navbar/navbartest.h \
    utils/digitalinput/digitalinput.h \
    utils/digitalinput/digitalinputtest.h \
    utils/button/groupbutton.h \
    test/colortest.h \
    common/global.h \
    common/platformhead.h

RESOURCES += \
    resource.qrc

QT_VER_STRING = $$[QT_VERSION];
QT_VER_STRING = $$split(QT_VER_STRING, ".")
QT_VER_MAJOR = $$member(QT_VER_STRING, 0)
QT_VER_MINOR = $$member(QT_VER_STRING, 1)
QT_VER_PATCH = $$member(QT_VER_STRING, 2)

win32{
    equals(QT_VER_MAJOR, 5){
        HEADERS += \
            utils/timeset/headutils.h \
            utils/timeset/timetotal.h \
            utils/timeset/timedisplay.h \
            utils/timeset/switchwidget.h \
            utils/timeset/timeset.h \
            utils/timeset/zoneset.h \
            utils/timeset/zonetable.h \
            utils/wheel/wheelwidget.h \
            utils/wheel/stringwheelwidget.h \
            utils/wheel/wheeltest.h

        SOURCES += \
            utils/timeset/headutils.cpp \
            utils/timeset/timetotal.cpp \
            utils/timeset/timedisplay.cpp \
            utils/timeset/switchwidget.cpp \
            utils/timeset/timeset.cpp \
            utils/timeset/zoneset.cpp \
            utils/timeset/zonetable.cpp \
            utils/wheel/wheelwidget.cpp \
            utils/wheel/stringwheelwidget.cpp \
            utils/wheel/wheeltest.cpp
    }

    equals(QT_MAJOR_VERSION, 4){

    }
}

#message(parse over)

FORMS += \
    test/colortest.ui
