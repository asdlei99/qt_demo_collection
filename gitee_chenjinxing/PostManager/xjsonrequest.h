#ifndef XJSONREQUEST_H
#define XJSONREQUEST_H


#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QUrl>

class XJsonRequest : public QObject
{
    Q_OBJECT

public:
    XJsonRequest(QObject *parent = 0);
    ~XJsonRequest();

    QUrl getUrl() const;
    void setUrl(const QUrl &value);

private:
    QNetworkAccessManager *m_accessManager;
    QUrl url;

public:

    //json 格式的提交 提交的是 json字符串
    void executePostByJson(QJsonObject &postData);

    //表单格式的提交(错误方式 不可用)
    void executePost(QJsonObject &postData);
    //表单格式的提交
    void executePost(QByteArray& data);
    void executePostTable(QByteArray& data);
    void executePostJson(QByteArray& data);

public slots:
    virtual void finishedSlot(QNetworkReply *reply);

};

#endif // WIDGET_H



