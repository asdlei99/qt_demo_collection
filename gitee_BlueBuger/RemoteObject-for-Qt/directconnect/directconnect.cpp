#include "directconnect.h"
#include <QJsonDocument>
#include <QJsonParseError>

DirectConnect::DirectConnect(QSharedPointer<TransferNewsReplica> ptr)
    : QObject(nullptr), m_ptr(ptr)
{
     QObject::connect(this, SIGNAL(sig_sendMessage(QString)), m_ptr.data(), SLOT(reveiceMessage(QString)));

     QObject::connect(m_ptr.data(), SIGNAL(lastMessageChanged(QString)), this, SLOT(slot_lastMessageChanged(QString)));
     QObject::connect(m_ptr.data(), SIGNAL(serverTime(QString)), this, SLOT(slot_serverTimeChanged(QString)));
     QObject::connect(m_ptr.data(), SIGNAL(testList(FooList)), this, SLOT(slot_testList(FooList)));
     QObject::connect(m_ptr.data(), SIGNAL(testMap(FooMap)), this, SLOT(slot_testMap(FooMap)));
     //QObject::connect(m_ptr.data(), SIGNAL(testStruct(FooStruct)), this, SLOT(slot_testStruct(FooStruct)));
//     QObject::connect(m_ptr.data(), SIGNAL(testStruct(test_Struct)), this, SLOT(slot_testStruct(test_Struct)));
     QObject::connect(m_ptr.data(),&TransferNewsReplica::testStruct,this,&DirectConnect::slot_testStruct);
     //QObject::connect(m_ptr.data(), SIGNAL(testVoidPointer(FooVoidPointer)), this, SLOT(slot_testVoidPointer(FooVoidPointer)));
     QObject::connect(m_ptr.data(), SIGNAL(testFooByteArray(FooByteArray)), this, SLOT(slot_testFooByteArray(FooByteArray)));
     QObject::connect(m_ptr.data(), SIGNAL(stateChanged(QRemoteObjectReplica::State,QRemoteObjectReplica::State)),
                      this, SLOT(slot_stateChanged(QRemoteObjectReplica::State,QRemoteObjectReplica::State)));
}

DirectConnect::~DirectConnect()
{

}

void DirectConnect::slot_lastMessageChanged(QString msg)
{
    //pros test
    QString text = "Pros: " + msg;

    emit sig_newMessage(text);
}

void DirectConnect::slot_serverTimeChanged(QString msg)
{
    //signal test
    QString text = "Signal: " + msg;

    emit sig_newMessage(text);
}

void DirectConnect::slot_testList(FooList foo)
{
    //Pod test
    QList<QString> list = foo.bar();

    for(auto itor = list.begin(); itor != list.end(); itor++)
    {
        QString text = "testList: " + *itor;
        emit sig_newMessage(text);
    }
}

void DirectConnect::slot_testMap(FooMap foo)
{
    QMap<int, QString> map = foo.bar();

    QMapIterator<int, QString> iter(map);
    while (iter.hasNext())
    {
        iter.next();
        QString text = "testMap: key:" + QString::number(iter.key()) + " value:" +  iter.value();
        emit sig_newMessage(text);
    }
}

void DirectConnect::slot_testStruct(test_struct foo)
{
    test_struct data = foo;

    emit sig_newMessage(data.debugStr());
}

//void DirectConnect::slot_testStruct(FooStruct foo)
//{
//        zjh_test_struct *dataPtr = (zjh_test_struct *)foo.bar();
//        emit sig_newMessage(dataPtr->body);
//}

//void DirectConnect::slot_testVoidPointer(FooVoidPointer data)
//{
//    zjh_test_struct *dataPtr = (zjh_test_struct *)data.bar();
//    emit sig_newMessage(dataPtr->body);
//}

void DirectConnect::slot_testFooByteArray(FooByteArray datagram)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson((const QByteArray &)datagram, &error);
    if (jsonDocument.isObject())
    {
        QJsonObject obj = jsonDocument.object();
        int value = obj["JsonByteArrayTest"].toInt();
        emit sig_newMessage("JsonByteArrayTest:" + QString::number(value));
    }
}

void DirectConnect::slot_stateChanged(QRemoteObjectReplica::State new_state, QRemoteObjectReplica::State old_state)
{
    //State test
    QMetaEnum metaEnum = QMetaEnum::fromType<QRemoteObjectReplica::State>();
    QString text = "State: ";

    text.append(metaEnum.valueToKey(new_state));
    text.append("->");
    text.append(metaEnum.valueToKey(old_state));

    emit sig_newMessage(text);
}

