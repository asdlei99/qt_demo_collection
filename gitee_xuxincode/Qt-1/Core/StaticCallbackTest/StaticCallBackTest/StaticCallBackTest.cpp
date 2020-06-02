#include "StaticCallBackTest.h"
#include <thread>
#include <QDebug>


/****************************************!
* @brief  ��������3��ص�һ������
* @param  [in]  CALLBACK_FUNC pFuncCallBack  ������ľ�̬�ص�����
* @param  [in]  void * data 
* @return void
****************************************/
void setCallBackFunc(CALLBACK_FUNC pFuncCallBack, void* data /*= nullptr*/)
{
    std::thread t([&pFuncCallBack]
    {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(3)); // 3��ص�һ��
            std::string str = "callback test";
            pFuncCallBack(str.c_str(), nullptr); // ���������ڴ�ִ��
        }
    });
    t.join();
}

//-------------------------����Ϊ��StaticCallBackTest���

// ��̬������ʼ��
StaticCallBackTest* StaticCallBackTest::s_this = nullptr;

StaticCallBackTest::StaticCallBackTest(QObject *parent)
    : QObject(parent)
{
    s_this = this; // �ؼ����

    // �����źż�����  ʹ��qDebug��ӡ
    connect(this, &StaticCallBackTest::signalTest, [this](const std::string& str) 
    {
        qDebug() << QString::fromStdString(str);
    });
}

/****************************************!
 * @brief  ��̬�ص�����
 * @param  [in]  const char * str  ����
 * @param  [in]  void * pData  
 * @return void CALLBACK  
 ****************************************/ 
void CALLBACK StaticCallBackTest::startFunc(const char *str, void *pData)
{
    // ʹ�þ�ָ̬�뷢���ź�
    emit s_this->signalTest(std::string(str));
}

/****************************************!
 * @brief  ���ô˺�������ص�
 * @return void  
 ****************************************/ 
void StaticCallBackTest::start()
{
    // ���þ�̬��Ա���� startFunc
    setCallBackFunc(&startFunc);

    /*******
    ע��
    Ҳ������doSomething(&startFunc, this);��this���󴫵ݹ�ȥ
    ********/
}