#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "DynamicListModel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    DynamicListModel *dynamicListModel = new DynamicListModel();
    engine.rootContext()->setContextProperty("dynamicModel", dynamicListModel);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    int retVal = app.exec();

    delete dynamicListModel;
    return retVal;
}
