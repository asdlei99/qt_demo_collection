#ifndef SENDFILES_H
#define SENDFILES_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class SendFiles;
}

class SendFiles : public QDialog
{
    Q_OBJECT

public:
    explicit SendFiles(QWidget *parent = 0);
    ~SendFiles();
    void setFilePath(QString txt);
    void getSendtojid(QString str)
    {
        tojid = str;
    }
public slots:
    void choosefile();//ѡ���ļ�
    void sendfile();//���� �ļ�

private:
    Ui::SendFiles *ui;
     QStringList  _file_to_send;
     QString tojid;
};

#endif // SENDFILES_H
