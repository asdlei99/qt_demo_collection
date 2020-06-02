#ifndef LISTWINDOW_H
#define LISTWINDOW_H

#include <QDialog>
#include "loginwindow.h"
#include "qfiletrans.h"
#include "mucroom.h"
#include "filereceivedlg.h"
#include <QXmppRosterIq.h>
#include <QXmppRosterManager.h>
#include <QXmppVCardIq.h>
#include <QXmppVCardManager.h>
#include <QXmppRegisterIq.h>
#include <QModelIndex>
#include <QListWidget>
#include <QXmppMucManager.h>
#include <QXmppLogger.h>
#include <QTreeView>
#include <QStandardItemModel>
#include <QSystemTrayIcon>
#include <QXmppCallManager.h>
#include <QCoreApplication>
#include <QAudioInput>
#include <QAudioOutput>
#include <QXmppRtpChannel.h>
#include <QDebug>
#include <QListWidgetItem>
#include <QMultiHash>
#include <QSet>
#include <QResizeEvent>


#include "skin/framelesswin.h"

namespace Ui {
class Listwindow;
}
class Chatwindow;
class RoomChat;
class Mucroom;

class MainDialog;
class Listwindow : public FramelessWin
{
    Q_OBJECT

protected:
    //void paintEvent(QPaintEvent *evt);

    void resizeEvent(QResizeEvent *evt);


public:
    explicit Listwindow(QWidget *parent = 0);
    virtual void SetupUI();
    ~Listwindow();
    typedef enum { GroupNewMsg,DoubleNewMsg,ChatNewMsg}  State;
    static   Listwindow *Instance();
   void contextMenuEvent(QContextMenuEvent*);//��������Ҽ�
    void moveToRightTop();  //��ʾ����λ��
    void closeEvent(QCloseEvent *e);
    QString Nicktojid(QString nick);
    QString Jidtonick(QString jid);
    void setpassword(QString);
    QSystemTrayIcon *createSysTray(QString fname,QObject *parent);//����
    void setChatlist(QString s)
    {
       chatlist_.removeOne(s);
    }
    void setGroupList(QString s)
    {
        groupChatlist.removeOne(s);
    }
    int showlist()
    {
       return chatlist_.size();
    }
    static QXmppMucManager* getMucmanager()
    {
        return mucmanager;
    }
    static QXmppCallManager* getcallmanager()
    {
        return callmanager;
    }
    Ui::Listwindow *getUI()
    {
        return ui;
    }

    QString getselfJID();
    void requestMucroomlist();  //���Ͳ���mucroom�ı���
   QMenu* creatTray();//�����Ҽ��˵�
   void creategroupwindow(QString);//����Ⱥ��id,��������
   void createchatwindow(QString);//���ݶԷ�jid���������촰��
  //  void changeEvent(QEvent *e);
   void refreshgrouplist(QString);

   MainDialog           *m_main;
public slots:
   void insertfilelist();
   void copychatsfile();
   void flushfilelist(RoomChat*);
   void iqReceived(const QXmppIq &iq);
   void handleModifypassmsg(QString);
   void slotaddnew(QString);
   void slotmodify();//�޸�����
   void Search();   //�����û�
   /*RostManager get all other friends' Jid*/
   void fileFinished(QXmppTransferJob*);
   void slotrosterReceived();//��ȡ���ѵ�list
  // void presenceChanged(const QString& bareJid, const QString& resource);
   /*VCardManager get all other friends' Nickname*/
   void slotvCardRecieved(const QXmppVCardIq&);  //���ܺ��ѵ�jid�������͵�ListWidget
   /*VCardManager get self Nickname*/
   void slotclientvCardRecieved();//��ȡ�Լ���jid
   void fileReceived(QXmppTransferJob*);   //  �ļ�����
   void doubleClicked(const QModelIndex &index);// ˫��
   void messageReceived(const QXmppMessage &msg);//  ������Ϣ
   void handlePrecenseReceive(const QXmppPresence &presence); // ����Precense
   void addChatWindow(QString jid,QString msg);//    ��Ϣ��ӵ�����
   void getRoom();//       ��ȡ���б�
   void getFriend();//      ��ȡ�����б�
   void getMucRoom();//    ��ȡ�������б�
   void clickSession();
   void slotremovefriend();
   void logMessage(QXmppLogger::MessageType,QString);//���շ���������Ϣ
   void handleGroupList(QString);             //�����鱨��
   void handleGroupChat(QModelIndex );           //˫����
   void handleMucroomList(QString);          //�����������鱨��
   void doubleclickmucRoom(QModelIndex);    //˫���������б�
   void addGroupMessages(QString,QString,QString);                 //��������Ϣ
  // void slotchangenick();   //�޸��ǳ�
   void changenick(QString new_nick);
   void slotNewMsg();
   void slotgroupchanged(QString);

   void trayIconActive(QSystemTrayIcon::ActivationReason reason);//����

   //void slotroomAdded(QXmppMucRoom*);
   //void lostacceptMucchat(QString,QString,QString);
   void slotQAction(); /**�Ҽ������˵������¼��ۺ���*/
   void Exet();
   void Disable();
   void Online();
   void slotListItemClick(QModelIndex); /*�������*/
   //������

   void addMucroomWindows(QString tojid,QString fromjid,QString roomname,QString msg);
   void on_NameList_customContextMenuRequested(const QPoint &pos);
   void uploadchats();//��Ⱥ�����¼�ϴ���������

   //����
   void slotcallrecieved(QXmppCall*);
  // void slotCallStateChanged(QXmppCall::State);
  // void slotAudioModeChanged(QIODevice::OpenMode);
signals:
    void recvMsg(QString frommsg,QString msg);  //�յ���Ϣ
    void addChatWindows(QString,QString);    //��Ϣ��ӵ����촰��
    void flashfilelist(RoomChat*);
// void setRosters(QStringList);
//void updateRosters();
    void handleSearch(QString);           //����ע���û�
    void handleModifypass(QString);
    void handleGroup(QString);             //������
    void handleMucroom(QString);            //�����������ź�
    void recvGroup(QString,QString,QString);
    void addGroupMessage(QString,QString,QString);  //�������Ϣ
    void SigNewMsg();    //   ����Ϣ
    void SigNewMsgs();
    void groupchanged(QString);//���ӻ���ɾ��Ⱥ��Ա�����ź�
    void roomchatshow(RoomChat*);
//������
    void recvMucMsg(QString fromjid,QString msg);
    void addMucroomWindow(QString tojid,QString fromjid,QString roomname,QString msg );
public:
    QString getself();
    QString getcurrentpath();
    QHash <QString, QString> hash_nameAndjid;
    QHash <QString, QString> hash_jidAndname;
    QHash <QString, Mucroom*> hash_mucjidAndmucwin;
    QHash <QString, QString> hash_mucnameAndjid;
    void setchattray(QString,bool);
    void setgrouptray(QString,bool);
    void setwindowsendflag(QString,bool);
private:
   Ui::Listwindow *ui;
   QString currentpath;
   QHash <QString,Chatwindow*>  winmap_;   //���촰��   ��Աjid+���ھ��
   QHash <QString,RoomChat*>  roommap_;   //�����촰��  ����+�鴰�ھ��
   QString nickNameSelf;     //�Լ���nick
   QString selfJID;          //�Լ���jid
   QString                  objectJID;
   QXmppVCardIq vCardself;
   QXmppRegisterIq registeriq;
   QStringList                 chatlist_;//�����б�
   QStringList               rosterList_;//�����б�
   static Listwindow* m_instance;
   QStringList                   roomlist;//�������б�
   QHash <QString,bool>    usrst_;//�û��Ƿ�����
   //QTreeView    *fr_;           //Ⱥ�б���
   //QTreeView  *muc_;          //������tree�б�
   QHash <QString,QStringList>   hash_wingroup;  //����Ϣ ����+��Ա�б�
   QStandardItemModel* model;
   QStandardItemModel* model_muc;
   QSystemTrayIcon             *trayIcon_;//����
   QMenu                       *trayMenu_;
   State                       msgState_;
  // QList<State>                msgState_list;
   Chatwindow *wd;
   RoomChat *rc;
   QString  str_addFriend;
   QString  str_removeFriend;

   QPixmap pixmap_on;
   QPixmap pixmap_off;
   QPixmap pixmap_tray_on;
   QPixmap pixmap_tray_off;
   QIcon   icon_tray; //����ͼ��

   QStringList    notifyList;
   QStringList    notifyGroupList;
   QStringList     groupChatlist; //�����б�
   static QXmppMucManager* mucmanager; //�����ҹ���
   static QXmppCallManager* callmanager;
   QListWidgetItem* item;
   QHash<QString,bool> hash_groupclicked;//������¼�Ƿ�˫��Ⱥ��,���������Ƿ���Ϣ���뵽������Ϣ��
   QHash<QString,QStringList> hash_groupmsg;//�洢����Ⱥ����Ϣ
   QHash<QString,bool> hash_chatclicked;//������¼�Ƿ����ض�jid����ͨ��,ͬ��
   QHash<QString,QStringList> hash_chatmsg;//�����洢���ߵ�����Ϣ
   QHash<QString,QSet<QString>> hash_jidAndgroup;//�洢jid����Ĺ�ϵ
   QHash<QString,bool> hash_chattray;//���������Ƿ���ʾ
   QHash<QString,bool> hash_grouptray;//ͬ��
   bool groupadd;//��־����,��־����Ϣ�ı��ԭ��
   bool filesend;//��־�Ƿ�����ļ�
   QString password;//�����洢password
   bool online;//������¼�Ƿ�����
   bool grouplistfinished;
};

#endif // LISTWINDOW_H
