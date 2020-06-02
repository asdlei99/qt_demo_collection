#include "MainWindow.h"
#include <QApplication>
#include "AppCfg.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    // 可以配置 打印日志到文件中去
    // qInstallMessageHandler(cfgMessageOutputToFile);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    qDebug() << "show main";

    return a.exec();
}
