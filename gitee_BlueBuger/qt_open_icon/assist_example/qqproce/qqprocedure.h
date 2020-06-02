/**
 ** @author:	   浓咖啡
 ** @date:	   2016.7.9
 ** @brief:      此程序是为了模拟桌面组件中的应用程序演示
 */

#ifndef QQPROCEDURE_H
#define QQPROCEDURE_H

#include <QtWidgets>
#include <QLocalSocket>
#include "desktopcmd.h"

class QQProcedure : public QWidget
{
    Q_OBJECT
public:
    explicit QQProcedure(QWidget *parent = 0);

private slots:
    void parseCmd();

private:
    QLocalSocket *qqsocket;
    void changeEvent(QEvent * event);
};

#endif // QQPROCEDURE_H
