#ifndef FILERECEIVEDLG_H
#define FILERECEIVEDLG_H

#include <QDialog>
#include <QCloseEvent>
#include <QXmppTransferManager.h>
#define LOCAL(x)  QString::fromLocal8Bit(x)
namespace Ui {
class FileReceiveDlg;
}

class FileReceiveDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FileReceiveDlg(QWidget *parent = 0);
    void     setFileName(const QString name);//�ļ���
    void     setFrom( const QString from);// ˭����
    void     setSize(qint64 size);// �ļ���С
    void     setbuttonstop();
    void     closeEvent( QCloseEvent *e);
    void     setfilejob(QXmppTransferJob*);
    void     changetosenddlg(QString);
    ~FileReceiveDlg();
public slots:
    void    slotAccept();
    void    slotReject();
    void    slotselectpath();
    void    slotfinished();
    void    sloterror(QXmppTransferJob::Error);
    void    slotProgress(qint64 transed,qint64 total);//������
private:
    Ui::FileReceiveDlg *ui;
    bool sendflg;//��־�Ƿ����ļ�
    QXmppTransferJob* filejob;
    bool abortflag;//��־�Ƿ���ֹ
};

#endif // FILERECEIVEDLG_H
