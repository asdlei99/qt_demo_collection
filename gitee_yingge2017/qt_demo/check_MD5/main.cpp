#include <QCoreApplication>
#include <qdir.h>
#include <qdebug.h>
#include <QCryptographicHash>
#include <qfile.h>

#if 0
uint8_t checkSumFunc(   uint8_t *pCur,uint32_t  size)
{
    uint32_t	rst = 0;
    uint32_t    i = 0;
    for(i= 0; i < size; ++i)
        rst += (*(pCur + i));
    return (uint8_t)(rst & 0xFF);
}
#endif
#if 0
QString bigCheckSum(const QString &sourceFilePath){
    QFile sourceFile(sourceFilePath);
    if(false == sourceFile.exists()){
        qDebug()<<"file not exist.";
    }


    qint64 fileSize = sourceFile.size();
    const qint64 bufferSize = 1000 * 1000;

    qDebug()<<"filse size:"<<fileSize;

    if (sourceFile.open(QIODevice::ReadOnly)) {
        char buffer[bufferSize];
        int bytesRead;
        int readSize = qMin(fileSize, bufferSize);

        QCryptographicHash hash(QCryptographicHash::Sha224);

        while (readSize > 0 && (bytesRead = sourceFile.read(buffer, readSize)) > 0) {
            fileSize -= bytesRead;
            hash.addData(buffer, bytesRead);
            readSize = qMin(fileSize, bufferSize);
        }

        sourceFile.close();
        return QString(hash.result().toHex());
    }else{
        qDebug()<<"open failed.";
    }

    return QString();
}
#endif

QString fileMd5(const QString &sourceFilePath) {

    QFile sourceFile(sourceFilePath);
    if(false == sourceFile.exists()){
        qDebug()<<"file not exist.";
    }

    qint64 fileSize = sourceFile.size();
    const qint64 bufferSize = 1000 * 1000;

    qDebug()<<"filse size:"<<fileSize;

    if (sourceFile.open(QIODevice::ReadOnly)) {
        char buffer[bufferSize];
        int bytesRead;
        int readSize = qMin(fileSize, bufferSize);

        QCryptographicHash hash(QCryptographicHash::Md5);

        while (readSize > 0 && (bytesRead = sourceFile.read(buffer, readSize)) > 0) {
            fileSize -= bytesRead;
            hash.addData(buffer, bytesRead);
            readSize = qMin(fileSize, bufferSize);
        }

        sourceFile.close();
        return QString(hash.result().toHex());
    }else{
        qDebug()<<"open failed.";
    }
    return QString();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString filePath = QDir::currentPath() +"/" +"test.zip";

    qDebug()<<"filePath:"<<filePath;

    QString md5Str = fileMd5(filePath);
    qDebug()<<md5Str;

    return a.exec();
}

//"bfd03a797da8406d332e5c121cafe4525ca9032da2abcd05702c72b5"
//"fc87ebca529e751a2bb125eb9d6cf7e6ecba979df1c0510aec763b34"
