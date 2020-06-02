#include "reqbatch.h"

#include <QDebug>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

#include "mainwindow.h"

ReqBatch::ReqBatch(QObject *parent)
    :XJsonRequest(parent),widget(nullptr)
{

}
//登录返回值
void ReqBatch::finishedSlot(QNetworkReply *reply)
{
//    if (reply->error()!= QNetworkReply::NoError)
//        return;
    QByteArray bytes = reply->readAll();

    //刷新界面数据
    ((MainWindow*)widget)->showData(bytes);
}

QWidget *ReqBatch::getWidget() const
{
    return widget;
}

void ReqBatch::setWidget(QWidget *value)
{
    widget = value;
}


