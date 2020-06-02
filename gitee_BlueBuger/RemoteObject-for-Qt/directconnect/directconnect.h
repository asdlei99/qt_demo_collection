#ifndef DIRECTCONNECT_H
#define DIRECTCONNECT_H

#include <QObject>
#include <QSharedPointer>

#include "rep_transfernews_replica.h"
#include "struct_def.h"

class DirectConnect : public QObject
{
    Q_OBJECT
public:
    DirectConnect(QSharedPointer<TransferNewsReplica> ptr);
    ~DirectConnect() override;

signals:
    void sig_sendMessage(QString);
    void sig_newMessage(QString);

protected slots:
    void slot_lastMessageChanged(QString);
    void slot_serverTimeChanged(QString);
    void slot_testList(FooList);
    void slot_testMap(FooMap);
    void slot_testStruct(test_struct);
    //void slot_testStruct(FooStruct);
    //void slot_testVoidPointer(FooVoidPointer);
    void slot_testFooByteArray(FooByteArray datagram);
    void slot_stateChanged(QRemoteObjectReplica::State, QRemoteObjectReplica::State);

private:
    QSharedPointer<TransferNewsReplica> m_ptr;
};

#endif // DIRECTCONNECT_H
