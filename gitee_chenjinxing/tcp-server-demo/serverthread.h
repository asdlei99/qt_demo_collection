#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>

class ServerThread : public QThread
{
public:
    ServerThread();

protected:
    virtual void run();

public:
    void startServer();
};

#endif // SERVERTHREAD_H
