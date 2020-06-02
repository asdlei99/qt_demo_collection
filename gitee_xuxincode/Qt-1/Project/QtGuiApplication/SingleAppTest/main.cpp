#include "SingleAppTest.h"
#include <QtWidgets/QApplication>
#include <QDir>
#include <QLockFile>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // �����Գ���idȡ��ΪSingleAppTest
    QString path = QDir::temp().absoluteFilePath("SingleAppTest.lock");
    // path = C:/Users/yu/AppData/Local/Temp/SingleAppTest.lock  
    QLockFile lockFile(path);

    bool isLock = lockFile.isLocked();
    // bool QLockFile::tryLock(int timeout = 0)
    // tryLock���Դ��������ļ����˺��������������򷵻�true; ���򷵻�false��
    // �����һ�����̣�����һ���̣߳��Ѿ����������ļ�����˺��������ȴ�timeout����
    if (!lockFile.tryLock(100)) 
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("The application is already running.\n"
            "Allowed to run only one instance of the application.");
        msgBox.exec();
        return 1;
    }

    SingleAppTest w;
    w.setFixedSize(250, 150);
    w.show();
    return a.exec();
}
