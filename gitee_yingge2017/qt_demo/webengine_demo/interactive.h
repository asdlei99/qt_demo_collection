#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include <QObject>

class Interactive : public QObject
{
    Q_OBJECT
public:
    explicit Interactive(QObject *parent = nullptr);

signals:
//    void sigSend(const QString&);
    void sigSend();
public slots:
    void slotRunJS(  bool &);
//    void slotRev(const QString&);
    void slotRev();
};

#endif // INTERACTIVE_H
