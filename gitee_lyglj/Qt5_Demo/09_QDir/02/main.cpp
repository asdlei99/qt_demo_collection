#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = "E:/Qt/test";

    QDir dir(path);
    if(!dir.exists())
    {
        qDebug() << "Creating " << path << "directory";
        dir.mkpath(path);
    }
    else
    {
        qDebug() << path << " already exists";
    }

    return a.exec();
}
