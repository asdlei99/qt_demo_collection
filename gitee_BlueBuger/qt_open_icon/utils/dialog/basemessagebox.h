/**
 ** @author:	   浓咖啡
 ** @date:	   2016.7.14
 ** @brief:      提示框基组件
 */

#ifndef BASEMESSAGEBOX_H
#define BASEMESSAGEBOX_H

#include "baselabel.h"
#include "basebutton.h"
#include "utilscommon.h"

class BaseMessageBox : public QDialog
{
    Q_OBJECT
public:
    enum RESULT{
        CANCEL = 0,
        OK
    };
    explicit BaseMessageBox(BaseLabel *labIcon, const QString &title,\
                            const QString &info, const QString &style = QString(),\
                            bool showCancel = true, int w=250, int h=150);
protected slots:
    void okSlot();
    void cancelSlot();
    void doneOk();
    void doneCancel();

protected:
    BaseLabel *labIcon;
    BaseButton *closeBtn;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    bool mousePressed;              //鼠标是否按下
    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标

    void setStyle(const QString &style);
    void showInCenter();
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // BASEMESSAGEBOX_H
