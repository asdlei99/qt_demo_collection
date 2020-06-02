/**
 ** @author:	   浓咖啡
 ** @date:	   2016.10.12
 ** @brief:      qq应用程序示例
 */
#ifndef QQPROCEDURE_H
#define QQPROCEDURE_H

#include "procedure.h"

class QQProcedure : public Procedure
{
    Q_OBJECT
public:
    QQProcedure();

private:
    virtual BaseButton *createIcon();
};

#endif // QQPROCEDURE_H
