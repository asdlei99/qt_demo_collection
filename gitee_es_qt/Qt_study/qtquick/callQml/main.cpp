#include "ChangeQmlColor.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QColor>

int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    /*
    QQuickView viewer;
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setSource(QUrl("qrc:///main.qml"));
    viewer.show();
    */
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject * root = NULL;//= qobject_cast<QObject*>(viewer.rootObject());
    QList<QObject*> rootObjects = engine.rootObjects();
    int count = rootObjects.size();
    qDebug() << "rootObjects = " << count;
    for(int i = 0; i < count; i++)
    {
        if(rootObjects.at(i)->objectName() == "rootObject")
        {
            root = rootObjects.at(i);
            break;
        }
    }

    ChangeQmlColor changeQmlColor(root);
    QObject * quitButton = root->findChild<QObject*>("quitButton");
    if(quitButton)
    {
        QObject::connect(quitButton, SIGNAL(clicked()), &app, SLOT(quit()));
    }

    QObject *textLabel = root->findChild<QObject*>("textLabel");

    if(textLabel)
    {
        //1. failed call
        // bool bRet = QMetaObject::invokeMethod(textLabel, "setText", Q_ARG(QString, "world hello"));
        bool bRet = textLabel->setProperty("text", "world hello");
        qDebug() << "call setText return - " << bRet;
        textLabel->setProperty("color", QColor::fromRgb(255,0,0));
        bRet = QMetaObject::invokeMethod(textLabel, "forceLayout");
        qDebug() << "call doLayout return - " << bRet;
    }

    return app.exec();
}
