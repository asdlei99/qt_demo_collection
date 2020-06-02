/**
 ** @author:	   浓咖啡
 ** @date:	   2016.7.12
 ** @brief:      版本差异化头文件解决方案
 */

#ifndef PLATFORMHEAD_H
#define PLATFORMHEAD_H

#include <QObject>
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
    #include <QtGui>
#else
    #include <QtWidgets>
#endif

#endif // PLATFORMHEAD_H
