#include "transfernews.h"
#include "struct_def.h"
#include <QDateTime>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QMap>
#include <QDebug>

TransferNews::TransferNews(QObject *parent)
    : TransferNewsSimpleSource(parent)
{
    m_timer = new QTimer(this);
    m_timer->start(2500);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(sendServerTime()));
}

TransferNews::~TransferNews()
{
    m_timer->stop();
}

void TransferNews::reveiceMessage(QString msg)
{
    setLastMessage(msg);

    qDebug() << msg;
}

void TransferNews::sendServerTime()
{
    //1.test QString type.
     QString message = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
     emit serverTime(message);

     //2.test QList type.
     QList<QString> list;
     list << "123" << "456" << "789";
     emit testList(FooList(list));


     //3.test QMap type.
     QMap<int, QString> map;
     map.insert(1, "testMap1");
     map.insert(2, "testMap2");
     map.insert(3, "testMap3");
     emit testMap(FooMap(map));

     //4.test QByteArray type.
     QJsonObject bodyObject;
     bodyObject.insert("JsonByteArrayTest", QJsonValue(222));
     emit testFooByteArray(FooByteArray(QJsonDocument(bodyObject).toJson()));

     //5.test struct type.
     test_struct data;
     data.type = 2;
     data.body = "ddddddddd";
     data.array[0] = 0;
     data.array[1] = 11;
     data.barr[0] = false;
     data.barr[1] = true;
     emit testStruct(data);

     qDebug() << message;
}
