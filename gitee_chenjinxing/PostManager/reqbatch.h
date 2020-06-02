#ifndef XREQBATCH_H
#define XREQBATCH_H
#include "xjsonrequest.h"
#include <QWidget>

class ReqBatch : public XJsonRequest
{

public:

    static ReqBatch & Instance()
    {
        static ReqBatch T;
        return T;
    }
    QWidget *getWidget() const;
    void setWidget(QWidget *value);

    virtual void finishedSlot(QNetworkReply *reply);


private:
    QWidget *widget;
    ReqBatch(QObject *parent = 0);
};

#endif // ReqBatch_H

