#ifndef TRANSFERNEWS_H
#define TRANSFERNEWS_H

#include <QObject>
#include <QTimer>
#include "rep_transfernews_source.h"

class TransferNews : public TransferNewsSimpleSource
{
    Q_OBJECT
public:
    explicit TransferNews(QObject *parent = nullptr);
    ~TransferNews();

public slots:
    void reveiceMessage(QString msg) override;
    void sendServerTime();

private:
    QTimer *m_timer;
};

#endif // TRANSFERNEWS_H
