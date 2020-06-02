#ifndef UTILSCOMMON_H
#define UTILSCOMMON_H

#include "platformhead.h"

namespace utilscommon {

//设置阴影
void setShadow(QWidget *w, qreal blurRadius=10, qreal dx=5, qreal dy=5);

//从文件读出内容并转为QString
QString readFile(const QString &path);

//设置自启动
void autoRunWithSystem(QString AppName, QString AppPath);
}


#endif // UTILSCOMMON_H
