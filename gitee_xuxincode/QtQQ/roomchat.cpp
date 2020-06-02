#include "roomchat.h"
#include "ui_roomchat.h"
#include "ui_widget.h"
#include "listwindow.h"
#include "qfiletrans.h"

#include "addfiles.h"
#include "setdlg.h"

#include "loginwindow.h"
#include "session.h"

#include <QDebug>
#include <QMenu>
//#include <file_historys.h>
#include <QMessageBox>
#include <QTextCodec>
#include <QDir>
#include <QWebFrame>
#include <QtWebKit>
#include <QDesktopServices>
#include <QProcess>
#include <QFileDialog>

RoomChat* RoomChat::instance = NULL;
RoomChat::RoomChat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomChat)
{
    ui->setupUi(this);
    instance = this;
    flag_down = 0;
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    Qt::WindowFlags flags=Qt::Dialog;
        flags |=Qt::WindowMinimizeButtonHint |Qt::WindowMaximizeButtonHint;
        setWindowFlags(flags);
    setWindowTitle(key);
    QFile source(":/style.html");
    source.open(QIODevice::ReadOnly);
    ui->webView->setHtml(QString::fromUtf8(source.readAll().constData()));
    source.close();

    commit = false;
    chat = new chats(this);
    version_reset = false;
    msgflag = true;
    flushflag = false;
    ui->tabWidget->setMovable(true);

     connect(ui->listWidget,SIGNAL(doubleClicked(QModelIndex)),Listwindow::Instance(),SLOT(doubleClicked(QModelIndex)));
     connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(sendMessages()));
   // connect(ui->lineEdit,SIGNAL(returnPressed()),ui->lineEdit,SLOT(clear()));
     connect(ui->pushButton,SIGNAL(clicked()),ui->textEdit_2,SLOT(clear()));

     connect(this,SIGNAL(addnewfreind(QString)),Listwindow::Instance(),SLOT(slotaddnew(QString)));
     connect(ui->bt_chats,SIGNAL(clicked()),this,SLOT(setchats()));
     connect(ui->webView->page(),SIGNAL(repaintRequested(QRect)),this,SLOT(slotloadmessage(QRect)));
     timer = startTimer(600000);
     set_path(Listwindow::Instance()->getcurrentpath() + "/fileshare/");
     set_remotepath(Loginwindow::getloginInstance()->getfileshare());
     connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(flushfilelist(int)));

     connect(ui->file_wid->ui->pushButton,SIGNAL(clicked()),this,SLOT(upload()));
     connect(ui->file_wid->ui->returnButton,SIGNAL(clicked()),this,SLOT(download()));
}

RoomChat::~RoomChat()
{
    killTimer(timer);
    delete ui;
    delete chat;
}
 //���ͺ���
void RoomChat::pushFriend(QStringList &list)
{
    ui->listWidget->clear();
    QStringList::iterator it = list.begin();
    for(; it != list.end(); ++it)
    {
         QStringList str1=selfjid_.split("/");
         QString str2= str1.at(0);
       if(*it!= str2){
           QString str = Listwindow::Instance()->Jidtonick(*it);
           if(str.isEmpty())
               str = *it;
        ui->listWidget->addItem(str);
      }
   }
}

  //������Ϣ
void  RoomChat::sendMessages()
{
    QString body= ui->textEdit_2->toPlainText();
    if(body.isEmpty())
    {
        QMessageBox::information(this,LOCAL("��ʾ"),LOCAL("���ܷ��Ϳ���Ϣ"),0);
        return;
    }

    QStringList::iterator it = groupchatlist.begin();
    for(it; it != groupchatlist.end(); ++it)
    {
        QString str ="<message  from=\"\" type=\"chat\" to=\"" ;
        str += *it;
        str += "\" id=\"";
        str += key;
        str += "\"><body>";
        str += body;
        str += "</body></message>";
        Loginwindow::getclient()->sendData(str.toUtf8());
       // qDebug()<<"sendMessage"<<str;
    }
    QString selfname = Listwindow::Instance()->getself();
    addMessage(selfname,body);
}
// // �����Ϣ
void RoomChat::addMessage(QString fromjid, QString msg)
{
   QFont  font = ui->webView->font();
   QString time = getCurrentTime();
   ui->webView->setFont(font);

   msgflag = true;
   QFile fd(Loginwindow::getloginInstance()->chatpath + key);
   if(!fd.open(QIODevice::Append))
   {
       QMessageBox::information(this,LOCAL("����"),LOCAL("�޷��������¼�ļ�"),0);
   }

   QString message = time + ":" + msg;
   message.replace("\n","<br>");
   message.replace("\\","\\\\");
   QString html = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='sender'>");
   html.append(fromjid);
   html.append(QString("</p><p class='triangle-right right'>%1</p></div>\")").arg(message));
   ui->webView->page()->mainFrame()->evaluateJavaScript(html);
   QString chat = time + fromjid + ":" + msg + "\n";
   QByteArray bchat = chat.toLocal8Bit().toBase64() + '\n';

   fd.write(bchat);
   fd.close();
}
void RoomChat::scrollToBottom()
{
    int h = ui->webView->page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
    ui->webView->page()->mainFrame()->setScrollBarValue(Qt::Vertical,h);
}
 //��ȡʱ��
QString RoomChat::getCurrentTime()
{
    QDateTime  dt = QDateTime::currentDateTime();
    QString format = tr("hh:mm:ss");
    QString ret = tr("[ ")+dt.toString(format) + tr(" ]");
    return ret;
}
void RoomChat::handleMessage(QString id,QString fromjid,QString body)
{
    qDebug()<<"first";
    QFont  font = ui->webView->font();
    QString time = getCurrentTime();
    QStringList str1=fromjid.split("/");
    QString str =  Listwindow::Instance()->Jidtonick(str1.at(0));
    if(str.isEmpty())
        str = fromjid;
    ui->webView->setFont(font);
    msgflag = true;
    QFile fd(Loginwindow::getloginInstance()->chatpath + key);
    if(!fd.open(QIODevice::Append))
    {
        QMessageBox::information(this,LOCAL("����"),LOCAL("�޷��������¼�ļ�"),0);
    }

    QString message = time;
    message += ":";
    message += body;
    message.replace("\n","<br>");
    message.replace("\\","\\\\");
    QString html = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='recver'>");
    html.append(str);
    html.append(QString("</p><p class='triangle-left left'>%1</p></div>\")").arg(message));
    ui->webView->page()->mainFrame()->evaluateJavaScript(html);
    QString chat = time + str + ":" + body + "\n";
    QByteArray bchat = chat.toLocal8Bit().toBase64() + '\n';

    fd.write(bchat);
    fd.close();
}
void RoomChat::closeEvent(QCloseEvent *e)
{
    this->close();
    qDebug()<<"close";
    QString id = this->windowTitle();
    Listwindow::Instance()->setgrouptray(id,true);
    Listwindow::Instance()->setGroupList(key);
}
void RoomChat::slotclosed()
{
    this->close();
    qDebug()<<"close";
    QString id = this->windowTitle();
    Listwindow::Instance()->setgrouptray(id,true);
    Listwindow::Instance()->setGroupList(key);
}
void RoomChat::keyPressEvent(QKeyEvent *e)
{
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *event = static_cast<QKeyEvent*>(e);
        if (event->key() == Qt::Key_Return && (event->modifiers() & Qt::ControlModifier))
        {
            sendMessages();
            ui->textEdit_2->clear();
        }
    }
}
void RoomChat::clearList()
{
    ui->listWidget->clear();
}

void RoomChat::set_remotepath(QString path)
{
    memset(remote_url,0,256);
    strcpy_s(remote_url,path.toStdString().c_str());
}
void RoomChat::set_path(QString s_path)
{
    memset(path,0,256);
    strcpy_s(path,s_path.toStdString().c_str());
}
void RoomChat::set_downloadflag()
{

}
void RoomChat::pull()
{

}

void RoomChat::repostatus()
{
/*    QString fpath = Listwindow::Instance()->getcurrentpath() + "/fileshare/";
    map<string,list<string>> smap = Git_client::getclient()->status(fpath.toStdString().c_str());
    if(smap.size() > 0)
    {
        QStringList infostrlist;
        QString infostr;
        map<string,list<string>>::iterator it = smap.begin();
        infostr += QString::fromLocal8Bit("δ�ύ�ļ�:");
        for(;it != smap.end();++it)
        {
            pair<string,list<string>> sp = *it;
            list<string> ls = sp.second;

            list<string>::iterator lit = ls.begin();
            for(;lit != ls.end();++lit)
                infostrlist.append((*lit).c_str());
        }
        infostrlist.toSet().toList();//�ڹ��������ݴ����е��ļ����ܳ����ظ�

        QStringList::iterator sit = infostrlist.begin();
        for(;sit != infostrlist.end();++sit)
            infostr += *sit;
        if(!pullflag)
        {
            QMessageBox message(QMessageBox::NoIcon,LOCAL("δ�����ļ�"),infostr + "\r\n" +
                            LOCAL("�Ƿ��ύδ������ļ�,���ѡ���,�����ļ��������ݶ�ʧ"),
                            QMessageBox::Yes | QMessageBox::No);
            if(message.exec() == QMessageBox::Yes)
            {
                slotaddfile();
            }
        }
        else
        {
            QMessageBox message(QMessageBox::NoIcon,LOCAL("��ͻ�ļ�"),infostr + "\r\n" +
                            LOCAL("���µ��ļ��뱾�ص��ļ������˳�ͻ,���괦����ύ,\r\nֱ���ύ���ܵ��±��ؼ�¼��ʧ"),
                            QMessageBox::Yes | QMessageBox::No);
            if(message.exec() == QMessageBox::Yes)
            {
                slotaddfile();
                return;
            }
            filepush();
        }
    }*/
}

void RoomChat::slotfiledownloadfinished()
{

}
void RoomChat::download()
{
    QUrl url = Session::Instance()->getURL() + "/file/group/"+key;
    ui->file_wid->loadURL(url);
}
void RoomChat::setfilename(QString name)
{
    memset(file_name,0,256);
    strcpy_s(file_name,name.toStdString().c_str());
}
void RoomChat::push()
{
}
void RoomChat::slotaddfile()
{

}
void RoomChat::upload()
{
    QString surl = Session::Instance()->getURL() + "/file/upload/"+key+":" + Session::Instance()->getJID();
    ui->file_wid->loadURL(QUrl(surl));
}

void RoomChat::slotpushfinished()
{

}
void RoomChat::filepush()//�����б���Ϣ
{

}
void RoomChat::get_filename(QString name)
{
    QStringList lpath = name.split('/');
    size_t i = lpath.count();
    QString fname = lpath[i - 1];
    strcpy_s(file_name,fname.toStdString().c_str());
}

void RoomChat::on_version_list_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem* item = ui->version_list->itemAt(pos);
    if(item==NULL)
    {
        return;           //����������Ҽ���λ�ò���treeItem�ķ�Χ�ڣ����ڿհ�λ���һ�
    }
    version_reset = true;
    QMenu* menu = new QMenu(this);
    QAction* act_mutiChat = new QAction(this);
    QVariant var = item->data(0,Qt::UserRole);
    version = var.toString();
    bool check = connect(act_mutiChat, SIGNAL(triggered()), this, SLOT(slotQAction()));
    Q_ASSERT(check);
    act_mutiChat->setText(LOCAL("�ָ��˰汾"));
    menu->addAction(act_mutiChat);
    menu->exec(QCursor::pos());
    delete menu;
    delete act_mutiChat;
}
void RoomChat::slotQAction()
{
    if(version_reset)
    {
        head = version;
        QMessageBox::information(this,LOCAL("��ʾ"),LOCAL("�ָ��ɹ�"),0);
    }
    version_reset = false;
}

void RoomChat::on_file_list_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem* item = ui->file_list->itemAt(pos);
    if(item==NULL)
    {
        return;           //����������Ҽ���λ�ò���treeItem�ķ�Χ�ڣ����ڿհ�λ���һ�
    }
    file_reset = true;
    QMenu* menu = new QMenu(this);
    QAction* act_mutiChat = new QAction(this);
    QAction* act_openfile = new QAction(this);
    QAction* act_opendir  = new QAction(this);
    QVariant var = item->data(0,Qt::UserRole);
    fname_fversion = var.toString();

    bool check = connect(act_mutiChat, SIGNAL(triggered()), this, SLOT(slotQActionfile()));
    Q_ASSERT(check);
    check = connect(act_openfile,SIGNAL(triggered()),this,SLOT(slotQActionopenfile()));
    Q_ASSERT(check);
    check = connect(act_opendir,SIGNAL(triggered()),this,SLOT(slotQActionopendir()));
    act_mutiChat->setText(LOCAL("�ָ����ļ����˰汾"));
    act_openfile->setText(LOCAL("�򿪴˰汾�ļ�"));
    act_opendir->setText(LOCAL("���ļ���"));
    menu->addAction(act_mutiChat);
    menu->addAction(act_openfile);
    menu->addAction(act_opendir);
    menu->exec(QCursor::pos());
    delete menu;
    delete act_mutiChat;
}
void RoomChat::slotQActionopendir()
{
    QString currentpath = QString("file:///") + Listwindow::Instance()->getcurrentpath() + "/fileshare/";
    bool is_open = QDesktopServices::openUrl(QUrl(currentpath, QUrl::TolerantMode));

    if(!is_open)
    {
        QMessageBox::information(this,LOCAL("��ʾ"),LOCAL("���ļ���ʧ�ܣ�"));
    }
}
void RoomChat::slotQActionfile()
{
    if(file_reset)
    {
        QStringList file_info = fname_fversion.split(',');
        if(file_info.count() < 2)
            return;

        QMessageBox::information(this,LOCAL("��ʾ"),LOCAL("�ָ��ɹ�"),0);
    }
    file_reset = false;
}

void RoomChat::slotQActionopenfile()
{
    QString name;
    if(file_reset)
    {
        QStringList file_info = fname_fversion.split(',');
        if(file_info.count()==2)
        {
            name = file_info.at(0);
        }
        else
            name = fname_fversion;
    }
    file_reset = false;

    QString filepath = Listwindow::Instance()->getcurrentpath() + "/fileshare/"+name;
    filepath = QString("file:///") + filepath;
    bool is_open = QDesktopServices::openUrl(QUrl(filepath, QUrl::TolerantMode));

    if(!is_open)
    {
        QMessageBox::information(this,LOCAL("��ʾ"),LOCAL("���ļ����ܱ���,������Ӧ��Ӧ�ó���"));
    }
}

void RoomChat::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem* item = ui->listWidget->itemAt(pos);
    if(item == NULL)
    {
        return;
    }
    QString name = item->text();
    str_addFriend = Listwindow::Instance()->hash_nameAndjid.value(name);
    QMenu* menu = new QMenu(this);
    QAction* act_mutiChat = new QAction(this);
    act_mutiChat->setText(LOCAL("��Ӻ���"));
    connect(act_mutiChat,SIGNAL(triggered()),this,SLOT(slotaddfriend()));
    menu->addAction(act_mutiChat);
    menu->exec(QCursor::pos());
}

void RoomChat::slotaddfriend()
{
    QString str = "<presence from=\"\" to=\"";
       str += addJID;
      str += "\" type=\"subscribe\"> </presence>";
    Loginwindow::getclient()->sendData(str.toLocal8Bit());
       emit addnewfreind(addJID);
}

//�����¼��ʾ
void RoomChat::setchats()
{
    QFile fd(Loginwindow::getloginInstance()->chatpath + key);
    fd.open(QIODevice::ReadOnly);
    chat->clear();
    while(!fd.atEnd())
    {
        QByteArray bchat = fd.readLine();
        QString str_chat = QString::fromLocal8Bit(QByteArray::fromBase64(bchat));
        chat->setchatsedit(str_chat);
    }
    chat->show();
}
//��ʼ�����촰��ʱ��
void RoomChat::chat_initwindow(QString fname)
{
    QFile fd(Loginwindow::getloginInstance()->chatpath + fname);
    if(!fd.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this,LOCAL("����"),LOCAL("�޷��������¼�ļ�"),0);
        return;
    }
    QTextStream ts(&fd);
    QString str_chat = ts.readAll();
    QStringList chatlist = str_chat.split('\n');
    if(chatlist.isEmpty())
    {
        return;
    }
    int i = chatlist.count();
    if(i > 20)
        i = 20;
    while(--i)
    {
        QString strtext = chatlist.at(chatlist.count() - i);
        QString strtext1 = QString::fromLocal8Bit(QByteArray::fromBase64(strtext.toLocal8Bit()));
        if(strtext1.isEmpty())
            return;
        QString senderinfo = strtext1.split("]").at(1);
        QString message = strtext1.split("]").at(0) + "]";
        QString sender = senderinfo.split(":").at(0);
        message += ":";
        message += senderinfo.split(":").at(1);
        message.replace("\n","<br>");
        message.replace("\\","\\\\");
        if(sender == Listwindow::Instance()->getself())
        {
            QString html = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='sender'>");
            html.append(sender);
            html.append(QString("</p><p class='triangle-right right'>%1</p></div>\")").arg(message.split('\n').at(0)));
            ui->webView->page()->mainFrame()->evaluateJavaScript(html);
        }
        else
        {
            QString html = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='recver'>");
            html.append(sender);
            html.append(QString("</p><p class='triangle-left left'>%1</p></div>\")").arg(message.split('\n').at(0)));
            ui->webView->page()->mainFrame()->evaluateJavaScript(html);
        }
    }
    fd.close();
}

QString RoomChat::getpath()
{
    QString gitpath = QString::fromLocal8Bit(path);
    return gitpath;
}
//��ʱ�ϴ�Ⱥ�����¼
void RoomChat::timerEvent(QTimerEvent *event)
{
    QString srcfile = Loginwindow::getloginInstance()->chatpath + key;
    QString destfile = Loginwindow::getloginInstance()->getfpath() + key;
    QString fpath = Loginwindow::getloginInstance()->getfpath();
    QString fserver = Loginwindow::getloginInstance()->getfserver();

    if(!Loginwindow::getloginInstance()->getchatsflag())
    {

    }
}

void RoomChat::slotloadmessage(QRect)
{
    int i = 12;
    if(msgflag)
    {
        scrollToBottom();
        msgflag = false;
    }
}
void RoomChat::flushfilelist(int)
{
    QString ckey = key;
    QUrl  url =  Session::Instance()->getURL() + "/file/group/"+ckey;
    ui->file_wid->loadURL(url);
}
//�ļ�������ɺ�,���ø���,�ύ��ťΪ����
void RoomChat::releasebutton()
{
    ui->bt_pull->setEnabled(true);
    ui->bt_push->setEnabled(true);
    ui->bt_add ->setEnabled(true);
}

void RoomChat::setcommitor(QString msg)
{
    memset(commitor,0,256);
    if(!msg.isEmpty())
        strcpy_s(commitor,msg.toStdString().c_str());
}

void RoomChat::setcommit_msg(QString msg)
{
    memset(commit_msg,0,256);
    if(!msg.isEmpty())
        strcpy_s(commit_msg,msg.toStdString().c_str());
}

void RoomChat::on_file_list_doubleClicked(const QModelIndex &index)
{
    QString name;
    QModelIndex parent = index.parent();
    if(parent.isValid())
    {
        name = parent.data().toString();
    }
    else
        name = index.data().toString();
    QString currentpath = QString("file:///") + Listwindow::Instance()->getcurrentpath() + "/fileshare/" + name;
    bool is_open = QDesktopServices::openUrl(QUrl(currentpath, QUrl::TolerantMode));
    if(!is_open)
    {
        QMessageBox::information(this,LOCAL("��ʾ"),LOCAL("���ļ���ʧ�ܣ�"));
    }
}
