#include "xjsonrequest.h"

#include <QJsonDocument>
#include <QJsonObject>
XJsonRequest::XJsonRequest(QObject *parent)
    : QObject(parent)
{
    m_accessManager = new QNetworkAccessManager();
    connect(m_accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));
}

XJsonRequest::~XJsonRequest()
{

}

QUrl XJsonRequest::getUrl() const
{
    return url;
}

void XJsonRequest::setUrl(const QUrl &value)
{
    url = value;
}

void XJsonRequest::executePostByJson(QJsonObject &postData)
{
    //POST
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json;charset=utf-8");

    QJsonDocument document;
    document.setObject(postData);
    QByteArray postBytes = document.toJson(QJsonDocument::Compact);
    m_accessManager->post(request,postBytes);
}

//表单格式的提交(错误方式 不可用)
void XJsonRequest::executePost(QJsonObject& postData)
{
    //POST
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QJsonDocument document;
    document.setObject(postData);
    QByteArray postBytes = document.toJson(QJsonDocument::Compact);
    m_accessManager->post(request,postBytes);
}

void XJsonRequest::executePost(QByteArray& data)
{
    //POST
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded;charset=utf-8");

    m_accessManager->post(request,data);
}
void XJsonRequest::executePostTable(QByteArray& data)
{
    //POST
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded;charset=utf-8");

    m_accessManager->post(request,data);
}
void XJsonRequest::executePostJson(QByteArray& data)
{
    //POST
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json;charset=utf-8");

    m_accessManager->post(request,data);
}
void XJsonRequest::finishedSlot(QNetworkReply *reply)
{

}


