#include "deskwgt.h"
#include "qpixmaphelper.h"

#include <QPixmap>
#include <QPainter>

DeskWgt::DeskWgt(QWidget *parent) : QWidget(parent)
{

}
//重绘
void DeskWgt::paintEvent(QPaintEvent *)
{
    QPixmap showPix;
    if(this->isBeginGame)
        showPix.load(":/img/desk.jpg");
    else
        showPix.load(":/img/desk2.jpg");
    QPixmap round =QPixmapHelper::PixmapToTriangle(showPix,120);
    QPainter painter(this);
    painter.drawPixmap(0,0,round);
}

bool DeskWgt::getIsBeginGame() const
{
    return isBeginGame;
}

void DeskWgt::setIsBeginGame(bool value)
{
    isBeginGame = value;
    this->update();
}
