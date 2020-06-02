#ifndef DESKWGT_H
#define DESKWGT_H

#include <QWidget>

class DeskWgt : public QWidget
{
    Q_OBJECT
public:
    explicit DeskWgt(QWidget *parent = 0);

    bool getIsBeginGame() const;
    void setIsBeginGame(bool value);

signals:

public slots:

private:
    bool isBeginGame =false;
protected:
    void paintEvent(QPaintEvent *);

};

#endif // DESKWGT_H
