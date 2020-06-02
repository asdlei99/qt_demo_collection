#include "transfernews.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    TransferNews transferNews;

    QRemoteObjectHost srcNode(QUrl(QStringLiteral("local:replica")));
    srcNode.enableRemoting(&transferNews);

    return app.exec();
}
