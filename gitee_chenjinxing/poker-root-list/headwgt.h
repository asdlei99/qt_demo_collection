#ifndef HEADWGT_H
#define HEADWGT_H

#include <QWidget>
#include <QPaintEvent>


class HeadWgt : public QWidget
{
    Q_OBJECT
public:
    explicit HeadWgt(QWidget *parent = 0);

    QString getUserName() const;
    void setUserName(const QString &value);

    void updateView();

signals:

public slots:

private:
    QString userName ="";
protected:
    void paintEvent(QPaintEvent *);

    //鼠标悬停
    void enterEvent(QEvent *event);
    //鼠标离开
    void leaveEvent(QEvent *event);

    void mousePressEvent(QMouseEvent *);

};

#endif // HEADWGT_H
