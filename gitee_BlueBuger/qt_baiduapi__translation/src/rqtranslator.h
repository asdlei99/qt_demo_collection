#ifndef RQTRANSLATOR_H
#define RQTRANSLATOR_H


#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDateTime>
#include <QEventLoop>
#include <QPair>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class rQTranslator :public QObject
{
    Q_OBJECT
public:
    rQTranslator(const QString &appid,const QString &apiKey,QObject *parent=nullptr);

    BaiduTranslation();
public slots:
    QPair<bool, QString> translation(const QString &string, const QString &from = "auto", const QString &to = "auto");
private:
    QString m_appID;
    QString m_apiKey;

    QNetworkAccessManager  *transnetworkmgr;
};

#endif // RQTRANSLATOR_H
