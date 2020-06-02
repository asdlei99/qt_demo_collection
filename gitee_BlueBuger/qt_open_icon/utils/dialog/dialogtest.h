/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.23
 ** @brief:      消息对话框
 */
#ifndef DIALOGTEST_H
#define DIALOGTEST_H

#include "toast.h"
#include "basemessagebox.h"

class DialogTest : public QWidget
{
    Q_OBJECT
public:
    explicit DialogTest();

signals:

public slots:

private slots:
    void toastSlot();
    void warningSlot();
    void messageSlot();

private:

};

#endif // DIALOGTEST_H
