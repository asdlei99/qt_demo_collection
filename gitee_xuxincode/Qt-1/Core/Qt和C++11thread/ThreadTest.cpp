#include "ThreadTest.h"
#include <thread>

ThreadTest::ThreadTest(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    // ���ź�  �����ť��ִ��test����
    connect(ui.pushButton, &QPushButton::clicked, [&]
    {
        test(); 
    });
}

/** @fn     ThreadTest::test
 *  @brief  ���Ժ���  ������水ť��ִ��
 *  @return void 
 */
void ThreadTest::test()
{
    // ������Ҫ֪���̵߳�ִ�н��runResult
    bool runResult{ false };

    // ����һ��loop����
    QEventLoop loop;
    // ���ź�  ��loop�յ������signalRunOver�źź��˳�ѭ��
    connect(this, &ThreadTest::signalRunOver, &loop, &QEventLoop::quit);
    
    // ����һ���̴߳�������  ������������  ��������ֱ�ӿ���һ���߳�ִ������������
    std::thread testThread([&]
    {
        // runResult = �������� �������ļ����ȵȺ�ʱ����  ʵ��ִ�е�����������λ��ִ��

        runResult = true;
        // ִ����ɺ� �����ź�  ��֪�߳�ִ�н���
        emit signalRunOver();
    });
    // �����߳�  ������������(�����߳�)
    testThread.detach();

    // �ڴ˴�ִ��ѭ��  �ȴ��̵߳�ִ�н��
    loop.exec();

    // �����߳�ִ����ɺ�ִ�����´���
    if (!runResult)
    {
        // ������  �������̽��治�Ῠ��
    }
}
