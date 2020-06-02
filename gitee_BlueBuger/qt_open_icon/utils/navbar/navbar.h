/**
 ** @author:	   浓咖啡
 ** @date:	   2016.12.8
 ** @brief:      导航栏
 */
#ifndef NAVBAR_H
#define NAVBAR_H

#include "basebutton.h"

class Navbar : public QWidget
{
    Q_OBJECT
public:
    explicit Navbar(int w, int h, BaseButton *leftbtn, QLabel *centerLab, BaseButton *rightbtn);

private:
    BaseButton *leftbtn;
    QLabel *centerLab;
    BaseButton *rightbtn;
};

#endif // NAVBAR_H
