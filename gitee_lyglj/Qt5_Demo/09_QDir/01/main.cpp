#include <QCoreApplication>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 目录分割符是正斜杠
    QDir dir1("E:/Qt");
    QDir dir2("E:/Qt/test");

    qDebug() << dir1.exists() << dir2.exists();

    QDir dir3;
    foreach(QFileInfo item, dir3.drives() )
    {
        qDebug() << item.absoluteFilePath();
    }

    return a.exec();
}

