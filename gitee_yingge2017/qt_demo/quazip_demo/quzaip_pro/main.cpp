#include <QCoreApplication>
#include "include/JlCompress.h"
#include <QDebug>
#include <qstringlist.h>
#include <qdir.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug()<<"start...";
    QDir dir;
    QString currentDirPath = dir.absolutePath();
    qDebug()<<dir.absolutePath();

    QString zipPath = currentDirPath + "/data.zip";
    QString targetDirPath = currentDirPath + "/data";
#if 1
    /**
    \param fileCompressed The name of the archive.
    \param dir The directory to compress.
    \param recursive Whether to pack the subdirectories as well, or
    just regular files.
    \return true if success, false otherwise.
    */
//  static bool compressDir(QString fileCompressed,
//          QString dir = QString(), bool recursive = true);
    bool re = JlCompress::compressDir(zipPath,targetDirPath);
    qDebug()<<"compress re:"<<re;
#endif

#if 0
    QString newDir = currentDirPath + "/data-new";
    QStringList list=JlCompress::extractDir(zipPath,newDir);//解压缩
    qDebug()<<"list size:"<<list.size();
#endif

    return a.exec();
}
