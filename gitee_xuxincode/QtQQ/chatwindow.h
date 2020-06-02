#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include <QXmppCallManager.h>
#include <QKeyEvent>
#include "listwindow.h"
#include "chats.h"
#include "sendfiles.h"

namespace Ui {
class Chatwindow;
}

class Chatwindow : public QDialog
{
    Q_OBJECT

public:
    enum ChatType { CommonChat, GroupChat};
   explicit Chatwindow(QWidget *parent = 0);
    ~Chatwindow();
     void closeEvent(QCloseEvent *e);
     void keyPressEvent(QKeyEvent *e);
     static  Chatwindow *Instance();
    void setTitle(QString str);   //���ô�������
    void setsendflag(bool);
    void chat_initwindow();
    void setcall(QXmppCall*);
    void setshowd(bool);
    bool getshowd();
    void calling();

    QString getCurrentTime();  //��ȡʱ��
    void scrollToBottom();

      void setChatJid(QString jid){
          chatjid_ = jid;
      }
      QString getChatJid() const {
          return chatjid_;
      }

      void setChatType(int t){
          chatType_ = t;
      }
      int getChatType() {
          return chatType_;
      }
      void setWinname(QString s);


 signals:
   // void  sendAddMessage(QString);
public slots:
    void slotclosed();
    void slotSendfile(); // �����ļ�
    void sendMessage();  // ������Ϣ
    void sendcall();//��������
    void setchats();//�õ������¼
    void handleMessage(QString fromjid,QString msg);//
   // void handleGroupMessage(QString fromjid,QString tojid,QString msg);
    void addMessage(QString fromjid,QString msg); // �����Ϣ
    //void addFriend();//�Ӻ���
    void slotCallStateChanged(QXmppCall::State);
    void slotAudioModeChanged(QIODevice::OpenMode);
    void slotcallrecieved(QXmppCall*);
    void slotcallstop();
    void slotjobstarted(QXmppTransferJob *);
    void slotmessageload(QRect);

    void slot_findfriend();
private:
    void startcall(QString);
    QString             chatjid_;
private:
    Ui::Chatwindow*     ui;
     int                chatType_;
     static Chatwindow* m_instance;
     QXmppCall*         call;
     chats* chat;
     bool filesend;//�����Ƿ����ļ�
     QXmppTransferJob* filejob;
     SendFiles *sf_;
     bool msgflag;
     bool showed;
     bool called;
};

#endif // CHATWINDOW_H
