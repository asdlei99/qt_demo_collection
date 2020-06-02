#include "global.h"
#include "buttontest.h"
#include "animationtest.h"
#include "dialogtest.h"
#include "baselabel.h"
#include "timetotal.h"
#include "wheeltest.h"
#include "navbartest.h"
#include "dialogtest.h"
#include "desktop.h"
#include "databasetest.h"
#include "customplottest.h"
#include "listtest.h"
#include "digitalinputtest.h"

#define NAVBAR

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#endif

#ifdef LABELTEST
    BaseLabel *w = new BaseLabel(MuiFont(), MuiFont::ICON_WEINXIN, 200, 100);
    w->show();
#elif defined BUTTONTEST
    ButtonTest *w = new ButtonTest;
    w->show();
#elif defined ANIMATIONTEST
    AnimationTest *w = new AnimationTest;
    w->show();
#elif defined DIALOGTEST
    DialogTest *w = new DialogTest;
    w->show();
#elif defined WHEELWIDGET && (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    bool touch = a.arguments().contains(QLatin1String("--touch"));
    WheelTest *w = new WheelTest(touch);
    w->show();
#elif defined TIMESET && (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    TimeTotal *w = new TimeTotal;
    w->show();
#elif defined NAVBAR
    NavBarTest *w = new NavBarTest;
    w->show();
#elif defined DESKTOP
    Desktop *w = new Desktop;
    w->show();
#elif defined LIST
    ListTest *w = new ListTest;
    w->show();
#elif defined QCustomPlot
    CustomplotTest *w = new CustomplotTest;
    w->show();
#elif defined DATABASE
    DatabaseTest *database = new DatabaseTest;
    database->test();
    return 0;
#elif defined DIGITALINPUT
    DigitalInputTest *w = new DigitalInputTest;
    w->show();
#endif

#ifdef RUN_EMBEDDED
    QWSServer::setCursorVisible(false);
#else
    w->move((qApp->desktop()->width()-w->width())/2, (qApp->desktop()->height()-w->height())/2);
#endif

    return a.exec();
}
