#include "SingleAppTest2.h"
#include <QtWidgets/QApplication>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // �����ź���
    QSystemSemaphore semaphore("SingleAppTest2Semaphore", 1);  
    // �����ź�������ֹ����ʵ��ͨ�������ڴ�һ����
    semaphore.acquire(); 

#ifndef Q_OS_WIN32
    // ��linux / unix �����쳣���������ڴ治�����
    // ��������Ҫ�ṩ�ͷ��ڴ�Ľӿڣ������ڳ������е�ʱ�����������ڴ� �������
    QSharedMemory nix_fix_shared_memory("SingleAppTest2");
    if (nix_fix_shared_memory.attach()) 
    {
        nix_fix_shared_memory.detach();
    }
#endif
    // ����һ�������ڴ�  ��SingleAppTest2����ʾһ���ڴ�ı�ʶkey ����ΪΨһ����ı�ʶ
    QSharedMemory sharedMemory("SingleAppTest2");  
    // �����Ƿ��Ѿ�����
    bool isRunning = false;
    // ��ͼ�������ڴ�ĸ������ӵ����еĶ��С�
    if (sharedMemory.attach()) 
    {
        // ����ɹ�����ȷ���Ѿ���������ʵ��
        isRunning = true; 
    }
    else 
    {
        // ��������һ�ֽ��ڴ�
        sharedMemory.create(1); 
        // ȷ������������ʵ��
        isRunning = false;     
    }
    semaphore.release();

    // ������Ѿ�������Ӧ�ó����һ��ʵ������ô���ǽ�֪ͨ�û���
    if (isRunning) 
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("The application is already running.\n"
            "Allowed to run only one instance of the application.");
        msgBox.exec();
        return 1;
    }

    SingleAppTest2 w;
    w.setFixedSize(250, 150);
    w.show();
    return a.exec();
}
