#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QRemoteObjectNode repNode;
    repNode.connectToNode(QUrl(QStringLiteral("local:replica")));

    QSharedPointer<TransferNewsReplica> ptr;
    ptr.reset(repNode.acquire<TransferNewsReplica>());

    MainWindow w(ptr);
    w.show();

    return app.exec();
}
