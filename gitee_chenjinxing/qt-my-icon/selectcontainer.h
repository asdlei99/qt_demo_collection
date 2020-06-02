#ifndef SELECTCONTAINER_H
#define SELECTCONTAINER_H

#include <QObject>
#include <QVector>
#include <QAction>
#include <QSignalMapper>
class SelectContainer : public QObject
{
    Q_OBJECT
private:
    QVector<QAction*> contaioner;
    bool canMultiple =false;
    QSignalMapper *signalMapper;
public:
    explicit SelectContainer(QObject *parent = 0,bool canMultiple =false);

    bool getCanMultiple() const;
    void setCanMultiple(bool value);

    QSignalMapper *getSignalMapper() const;
    void setSignalMapper(QSignalMapper *value);

    bool addAction(QAction* action);

signals:
    //选择了某个项
    void actionTriggered(int var);
    //取消了某个项
    void actionUnTriggered(int var);
public slots:
    void actionTrigger(int var);
};

#endif // SELECTCONTAINER_H
