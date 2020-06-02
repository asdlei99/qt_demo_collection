#include <qapplication.h>
#include <stdio.h>
#include <stdlib.h>
#include <QFile>
#include <QTextStream>
#include "AppCfg.h"

void cfgMessageOutputToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString txtMessage;

    switch (type)
    {
        case QtDebugMsg:    //调试信息提示
            txtMessage = QString("Debug: %1 (%2)").arg(msg, context.function);
            break;
        case QtInfoMsg:
            txtMessage = QString("Info: %1 (%2)").arg(msg, context.function);
            break;
        case QtWarningMsg:    //一般的warning提示
            txtMessage = QString("Warning: %1 (%2)").arg(msg, context.function);
            break;

        case QtCriticalMsg:    //严重错误提示
            txtMessage = QString("Critical: %1 (%2)").arg(msg, context.function);
            break;

        case QtFatalMsg:    //致命错误提示
            txtMessage = QString("Fatal: %1 (%2)").arg(msg, context.function);
            abort();
    }

    //保存输出相关信息到指定文件
    QFile outputFile("cfgMessageLog.txt");
    outputFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream textStream(&outputFile);
    textStream << txtMessage << endl;
}
