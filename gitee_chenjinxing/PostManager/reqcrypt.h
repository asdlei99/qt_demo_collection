#ifndef REQCRYPT_H
#define REQCRYPT_H

#include <QString>
#include <QByteArray>
#include <QCryptographicHash>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

class ReqCrypt{
public:
    static QByteArray getKey(){
        return "Fes#7^$N#0COI60E";
    }
public:
    static QString md5Key(QByteArray reqBytes)
    {
        reqBytes+=getKey();
        //md5加密
        QByteArray bytePwdMd5 = QCryptographicHash::hash(reqBytes, QCryptographicHash::Md5);
        bytePwdMd5 =bytePwdMd5.toPercentEncoding();
        QString strPwdMd5 = bytePwdMd5.toHex(); //加密后的数据
        return bytePwdMd5;
    }
    static QByteArray md5Key(QJsonObject req)
    {
        QJsonDocument document;
        document.setObject(req);
        QByteArray reqBytes = document.toJson(QJsonDocument::Compact);

        reqBytes+=getKey();
        //md5加密
        QByteArray bytePwdMd5 = QCryptographicHash::hash(reqBytes, QCryptographicHash::Md5);
        //QByteArray byteArrayUrlEncode=bytePwdMd5.toPercentEncoding();//没有用到
        QByteArray strPwdMd5 = bytePwdMd5.toHex(); //加密后的数据
        QByteArray byteArrayUrlEncode=strPwdMd5.toPercentEncoding(); //UrlEncode
        return byteArrayUrlEncode;
    }

};
#endif // REQCRYPT_H
