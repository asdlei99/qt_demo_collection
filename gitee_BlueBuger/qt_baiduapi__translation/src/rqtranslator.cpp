#include "rqtranslator.h"

#include <QDebug>


rQTranslator::rQTranslator(const QString &appid, const QString &apiKey, QObject *parent):
    QObject(parent)
{
    m_appID = appid;
    m_apiKey = apiKey;
}

QPair<bool, QString> rQTranslator::translation(const QString &string, const QString &from, const QString &to)
{
    transnetworkmgr = new QNetworkAccessManager;
    QString format("http://api.fanyi.baidu.com/api/trans/vip/translate?q=%1&from=%2&to=%3&appid=%4&salt=%5&sign=%6");

    uint time = QDateTime::currentDateTime().toTime_t();
    srand(time);
    QString salt = QString::number(rand());
    QString str1 = m_appID+string+salt+m_apiKey;
    QCryptographicHash md(QCryptographicHash::Md5);
    md.addData(str1.toUtf8());
    QString str1md5 = md.result().toHex();

    QNetworkRequest request;
    request.setRawHeader("Content-Type", "application");
    request.setUrl(QUrl(format.arg(string, from, to, m_appID,salt,str1md5).toUtf8()));

    QNetworkReply *reply = transnetworkmgr->get(request);
    QByteArray responseData;
    QEventLoop eventLoop;
    connect(transnetworkmgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();       //block until finish

    QPair<bool,QString> ret;
    ret.first = false;
    ret.second = "";

    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Error:" << reply->errorString();
        return ret;
    }
    responseData = reply->readAll();

    QJsonObject data(QJsonDocument::fromJson(responseData).object());
    if(!data.contains("trans_result")
            || data["trans_result"].toArray().isEmpty()
            || !data["trans_result"].toArray()[0].toObject().contains("dst")) { return ret; }

    ret.first = true;
    ret.second = data["trans_result"].toArray()[0].toObject()["dst"].toString();
}

