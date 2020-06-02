#include "ContactModel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<ContactModel>("Backend", 1, 0, "ContactModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/contactlist.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
