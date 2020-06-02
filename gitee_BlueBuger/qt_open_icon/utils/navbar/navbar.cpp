/**
 ** @author:	   浓咖啡
 ** @date:	   2016.12.8
 ** @brief:      导航栏
 */

#include "navbar.h"

/**
 * @brief Navbar::Navbar
 * @param w 导航栏总长度
 * @param h 导航栏总高度
 * @param leftbtn 最左侧按钮，如果不需要传NULL
 * @param centerLab 中间标题栏，必须传入
 * @param rightbtn 最右侧按钮，如果不需要传NULL
 */
Navbar::Navbar(int w, int h, BaseButton *leftbtn, QLabel *centerLab, BaseButton *rightbtn)
{
    int centerW = w;

    //整体布局
    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setMargin(0);
    lay->setSpacing(0);
    setFixedSize(w, h);

    if(NULL != leftbtn){
        this->leftbtn = leftbtn;
        leftbtn->setFixedSize(h, h);
        lay->addWidget(leftbtn);
        centerW = centerW - h;
    }

    centerLab->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    if(NULL != rightbtn){
        centerW = centerW - h;
        centerLab->setFixedSize(centerW, h);
        lay->addWidget(centerLab);

        lay->addWidget(rightbtn);
        this->rightbtn = rightbtn;
        rightbtn->setFixedSize(h, h);
        rightbtn->setFocusPolicy(Qt::NoFocus);
    }else{
        centerLab->setFixedSize(centerW, h);
        lay->addWidget(centerLab);
    }
}
