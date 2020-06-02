#include "bridge.h"
#include <QMessageBox>

bridge* bridge::instance()
{
    static bridge s_obj;
    return &s_obj;
}

bridge::bridge()
{
}

void bridge::showMsgBox()
{
    QMessageBox::aboutQt(0, tr("Qt"));
}
