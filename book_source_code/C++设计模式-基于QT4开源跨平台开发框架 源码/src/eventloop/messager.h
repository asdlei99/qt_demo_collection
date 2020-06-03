#ifndef MESSAGER_H
#define MESSAGER_H

#include <QObject>
#include <QString>
#include <QErrorMessage>

class Messager : public QObject {
    Q_OBJECT
 public:
    Messager (QString msg, QWidget* parent=0);

 public slots:
    void shout();

 private:
    QWidget* m_Parent;
    QErrorMessage* m_Message;
};

#endif

