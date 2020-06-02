#ifndef USERREGISTERRCV_H
#define USERREGISTERRCV_H

#include <QObject>
#include "user.h"
#include "receiver.h"
class UserRegisterRcv : public QObject,public Receiver
{
    Q_OBJECT
private:
    User addUser;
public:
    UserRegisterRcv();
    virtual void sendData();
    virtual void parseData(TcpSocket *socket, QDataStream &stream,const int &packSize);
signals:
    void newUser(User user);
public:
    User getAddUser() const;
    void setAddUser(const User &value);
};
#endif // USERREGISTERRCV_H
