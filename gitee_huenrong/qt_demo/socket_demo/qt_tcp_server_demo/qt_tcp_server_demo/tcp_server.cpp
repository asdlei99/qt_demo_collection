#include "tcp_server.h"
#include "ui_tcp_server.h"
#include <QDebug>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QMessageBox>
#include <time.h>
#include <QDateTime>
#include <stdio.h>


tcp_server::tcp_server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tcp_server)
{
    ui->setupUi(this);

    get_local_ip();     // 获取本机ip地址并xian显示到下拉框

    // 设置发送区默认显示内容
    ui->send_textEdit->append("hello client");

    bool hex_flag = ui->hex_checkBox->checkState();

    qDebug() << "hex_flag: " << hex_flag;
}

tcp_server::~tcp_server()
{
    delete ui;
}

/************************************************************************
函数名称: get_local_ip
函数功能: 获取本机ip地址
函数参数: 无
函数返回: 无
************************************************************************/
void tcp_server::get_local_ip(void)
{
    QString ip_address;
    QList<QHostAddress> ip_address_list = QNetworkInterface::allAddresses();
    for (int i=0; i<ip_address_list.size(); i++)
    {
        if (ip_address_list.at(i) != QHostAddress::LocalHost &&
                ip_address_list.at(i).toIPv4Address())
        {
            ip_address = ip_address_list.at(i).toString();
            // qDebug() << ip_address;  //debug

            // 将获取到的ip地址显示到ip地址下拉框中
            ui->ip_comboBox->addItem(ip_address);
        }
    }

    if (ip_address.isEmpty())
    {
        ip_address = QHostAddress(QHostAddress::LocalHost).toString();
    }
}

/************************************************************************
函数名称: init_tcp_server
函数功能: 初始化tcp服务器
函数参数: 无
函数返回: 无
************************************************************************/
bool tcp_server::init_tcp_server(void)
{
    // 启动一个tcp server
    user_tcp_server = new QTcpServer(this);

    // ip地址选择错误
    if (ui->ip_comboBox->currentText().isEmpty())
    {
        QMessageBox::information(this, tr("监听失败"), tr("未选择正确的ip地址"),
                                 QMessageBox::Ok);

        return false;
    }

    // 未输入端口号
    if (ui->port_lineEdit->text().isEmpty())
    {
        QMessageBox::information(this, tr("监听失败"), tr("未输入端口号"),
                                 QMessageBox::Ok);

        return false;
    }

    // 获取界面上前面显示的ip地址
    QHostAddress ip_address(ui->ip_comboBox->currentText());

    // 监听
    bool ret = user_tcp_server->listen(ip_address, ui->port_lineEdit->text().toUShort());
    if (false == ret)       // 监听失败，弹出提示
    {
        // qDebug() << "listen error: " << user_tcp_server->errorString();

        QMessageBox::information(this, tr("监听失败"), user_tcp_server->errorString(),
                                 QMessageBox::Ok);

        return false;
    }

    //来一个客户端连接，就会产生一个slot
    connect(user_tcp_server, SIGNAL(newConnection()), this, SLOT(slot_new_connection()));

    return true;
}

// 接收一个新连接产生的槽函数
void tcp_server::slot_new_connection(void)
{
    // 获取每个链接的客户端socket套接字
    user_tcp_socket = user_tcp_server->nextPendingConnection();

    if (nullptr == user_tcp_socket)
    {
        // qDebug() << "socket error";

        return;
    }

    // 获取客户端ip和port
    QString client_ip = user_tcp_socket->peerAddress().toString();
    quint16 client_port = user_tcp_socket->peerPort();

    // qDebug() << QString("client info: [%1:%2]").arg(client_ip).arg(client_port);

    // 显示当前连接的客户端信息
    ui->client_label->setText(QString("client: [%1:%2]").
                              arg(client_ip).
                              arg(client_port));

    // 关联读取数据槽函数
    connect(user_tcp_socket, SIGNAL(readyRead()), this, SLOT(slot_read_data()));
}

// 有数据需要读取的槽函数
void tcp_server::slot_read_data(void)
{
    QByteArray recv_data;
    QString show_data;

    // 接收数据
    recv_data = user_tcp_socket->readAll();

    // 如果hex复选框被选中，则需要将接收数据转换成hex格式
    if (ui->hex_checkBox->checkState())
    {
        // 将接收数据转换成hex，并转换成大写
        QString recv_data_hex = recv_data.toHex().toUpper();

        // 在字节间插入空格
        for (int i=0; i<recv_data_hex.length(); i+=2)
        {
            show_data += recv_data_hex.mid(i, 2);
            show_data += " ";
        }
    }
    else
    {
        show_data = recv_data.data();
    }

    // qDebug() << "show data: " << show_data;

    // 将接收到的数据显示到窗口
    ui->show_textEdit->append(QString("[%1]<-: %2").
                              arg(QTime::currentTime().toString("hh:mm:ss.zzz")).
                              arg(show_data));
}

// 侦听按钮
void tcp_server::on_listen_pushButton_toggled(bool checked)
{
    if (true == checked)        // 如果按钮被按下
    {
        if (true == init_tcp_server())      // 初始化服务器成功
        {
            // 更新按钮显示内容
            ui->listen_pushButton->setText(tr("断开"));
        }
    }
    else        // 按钮未被按下
    {
        // 断开链接
        user_tcp_server->close();
        user_tcp_socket->close();

        // 更新按钮显示内容
        ui->listen_pushButton->setText(tr("侦听"));
    }
}

// 发送数据按钮
void tcp_server::on_send_pushButton_clicked()
{
    // 未填入需要发送的数据
    if (ui->send_textEdit->toPlainText().isEmpty())
    {
        QMessageBox::information(this, tr("发送数据失败"), tr("请填入需要发送的数据"),
                                 QMessageBox::Ok);

        return;
    }

    // 获取需要发送的数据
    QString send_data = ui->send_textEdit->toPlainText();

    // 如果hex复选框被选中，则需要将数据转换成hex格式
    if (ui->hex_checkBox->checkState())
    {
        QByteArray send_data_hex = QByteArray::fromHex(send_data.toLatin1().data());

        // 发送hex数据
        user_tcp_socket->write(send_data_hex.data(),
                               send_data_hex.length());
    }
    else
    {
        // 发送数据
        user_tcp_socket->write(send_data.toStdString().c_str(),
                               strlen(send_data.toStdString().c_str()));
    }

    // 将发送数据显示到窗口
    ui->show_textEdit->append(QString("[%1]->: %2").
                              arg(QTime::currentTime().toString("hh:mm:ss.zzz")).
                              arg(send_data));
}

// 清除窗口按钮
void tcp_server::on_clear_windows_pushButton_clicked()
{
    ui->show_textEdit->clear();
}

// 清空发送区按钮
void tcp_server::on_clear_send_pushButton_clicked()
{
    ui->send_textEdit->clear();
}

// 输入框内容改变
void tcp_server::on_send_textEdit_textChanged()
{
    // 这里理想情况是判断当前输入的整个字符串
    // 这里实际只判断到了第一个合法字符位置(从后往前算)

    // 如果当前是hex模式，并且输入框有内容，则判断输入内容是否满足十六进制
    if (ui->hex_checkBox->checkState() && (!ui->send_textEdit->toPlainText().isEmpty()))
    {
        QString input_data = ui->send_textEdit->toPlainText();
        int input_len = input_data.length();
        char input_char = input_data[input_len - 1].toLatin1();

        // 输入的不是有效十六进制数据
        if (!(' ' == input_char ||
            ('0' <= input_char && input_char <= '9') ||
            ('a' <= input_char && input_char <= 'f') ||
            ('A' <= input_char && input_char <= 'F') ||
            ('\n' == input_char)))      // 排除按下回车键
        {
            // 弹出提示框
            QMessageBox::information(this, tr("发送数据格式错误"),
                                     tr("不是有效hex字符组合(\"0-9\", \"a-f\", \"A-F\", \" \") \n"
                                        "每两个字符间一个空格"),
                                     QMessageBox::Ok);

            // 获取当前文本光标
            QTextCursor current_cursor = ui->send_textEdit->textCursor();

            // 判断当前是否选中了文本，如果选中了文本则取消选中的文本
            if (current_cursor.hasSelection())
            {
                current_cursor.clearSelection();
            }

            // 删除光标前的字符
            current_cursor.deletePreviousChar();

            // 让光标移到删除后的位置
            ui->send_textEdit->setTextCursor(current_cursor);
        }
    }
}

// hex选择框状态改变
void tcp_server::on_hex_checkBox_stateChanged(int arg1)
{
    // 选择框未选中，则当前为字符串模式，设置默认显示内容
    if (0 == arg1)
    {
        ui->send_textEdit->clear();
        ui->send_textEdit->append("hello client");
    }
    else        // 选择框被选中，则当前为hex模式，设置默认显示内容
    {
        ui->send_textEdit->clear();
        ui->send_textEdit->append("AA BB");
    }
}
