#include "mythreada.h"

myThreadA::myThreadA(QString Text, int DelayMs)
{
    m_strText = Text;
    m_nDelayMs = DelayMs;
}

void myThreadA::run()
{
    while(true)
    {//这个就是子线程调用父类线程（谁new的它，在父类中要设置下为它的）一个名为SetMyText的函数，并传递参数
        QMetaObject::invokeMethod(this->parent(),"SetMyText",Q_ARG(QString, m_strText));
        msleep(m_nDelayMs);
    }
}
