/**
 ** @author:	    浓咖啡
 ** @date:          2017.9.26
 ** @brief:         存放一些全局配置
 */

#ifndef GLOBAL_H
#define GLOBAL_H

//#define RUN_EMBEDDED  //运行于嵌入式系统
#ifdef RUN_EMBEDDED
#include <QWSServer>
#endif

class Global
{
public:
    Global();
};

#endif // GLOBAL_H
