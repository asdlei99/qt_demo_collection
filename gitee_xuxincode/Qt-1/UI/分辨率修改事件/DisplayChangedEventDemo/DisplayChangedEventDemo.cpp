#include "DisplayChangedEventDemo.h"
#include "windows.h"
#include <QDebug>

DisplayChangedEventDemo::DisplayChangedEventDemo(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

bool DisplayChangedEventDemo::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    int msgType = msg->message;
    switch (msgType)
    {
    case WM_DISPLAYCHANGE:
    {
        // �ֱ����޸��¼� ��ȡ�����µķֱ�������
        int width = GetSystemMetrics(SM_CXSCREEN);
        int height = GetSystemMetrics(SM_CYSCREEN);

        qDebug() << "current system size: " << width << " " << height;
    }
    break;
    default:
        break;
    }

    return QWidget::nativeEvent(eventType, message, result);
}

/*
�ֱ����л�ʱ�������
current system size:  1600   900
current system size:  1280   720
current system size:  1920   1080
*/