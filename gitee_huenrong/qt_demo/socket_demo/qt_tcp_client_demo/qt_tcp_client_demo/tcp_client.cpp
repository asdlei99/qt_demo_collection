#include "tcp_client.h"
#include "ui_tcp_client.h"
#include <QDebug>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QMessageBox>
#include <time.h>
#include <QDateTime>
#include <stdio.h>


tcp_client::tcp_client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tcp_client)
{
    ui->setupUi(this);

    user_tcp_client = new QTcpSocket(this);

    // 关联读取数据槽函数
    connect(user_tcp_client, SIGNAL(readyRead()), this, SLOT(slot_read_data()));
}

tcp_client::~tcp_client()
{
    delete ui;
}

// 连接按钮
void tcp_client::on_link_pushButton_toggled(bool checked)
{
    if (ui->ip_lineEdit->text().isEmpty())
    {
        QMessageBox::information(this, tr("打开链接失败"),
                                 tr("请输入ip地址"),
                                 QMessageBox::Ok);

        return;
    }

    if (ui->port_lineEdit->text().isEmpty())
    {
        QMessageBox::information(this, tr("打开链接失败"),
                                 tr("请输入port"),
                                 QMessageBox::Ok);

        return;
    }

    if (true == checked)        // 按钮被按下
    {
        // 打开链接
        user_tcp_client->connectToHost(ui->ip_lineEdit->text(),
                                       ui->port_lineEdit->text().toUShort());

        if (user_tcp_client->waitForConnected(1000))     // 打开链接成功
        {
            ui->link_pushButton->setText(tr("断开"));
        }
        else    // 打开链接失败
        {
            QMessageBox::information(this, tr("打开链接失败"),
                                     user_tcp_client->errorString(),
                                     QMessageBox::Ok);
        }
    }
    else        // 按钮未被按下
    {
        // 关闭链接
        user_tcp_client->disconnectFromHost();
        // user_tcp_client->waitForDisconnected();

        ui->link_pushButton->setText(tr("连接"));
    }
}

// 发送数据按钮
void tcp_client::on_send_pushButton_clicked()
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
        user_tcp_client->write(send_data_hex.data(),
                               send_data_hex.length());
    }
    else
    {
        // 发送数据
        user_tcp_client->write(send_data.toStdString().c_str(),
                               strlen(send_data.toStdString().c_str()));
    }

    // 将发送数据显示到窗口
    ui->show_textEdit->append(QString("[%1]->: %2").
                                arg(QTime::currentTime().toString("hh:mm:ss.zzz")).
                                arg(send_data));
}

// 清空发送区按钮
void tcp_client::on_clear_send_pushButton_clicked()
{
    ui->send_textEdit->clear();
}

// 清空窗口按钮
void tcp_client::on_clear_windows_pushButton_clicked()
{
    ui->show_textEdit->clear();
}

// 有数据需要读取的槽函数
void tcp_client::slot_read_data(void)
{
    QByteArray recv_data;
    QString show_data;

    // 接收数据
    recv_data = user_tcp_client->readAll();

//    qDebug() << "len: " << recv_data.length();
//    qDebug() << "recv_data: " << recv_data;

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

    // 将接收到的数据显示到窗口
    ui->show_textEdit->append(QString("[%1]<-: %2").
                                arg(QTime::currentTime().toString("hh:mm:ss.zzz")).
                                arg(show_data));
}

// 输入框内容改变
void tcp_client::on_send_textEdit_textChanged()
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
void tcp_client::on_hex_checkBox_stateChanged(int arg1)
{
    // 选择框未选中，则当前为字符串模式，设置默认显示内容
    if (0 == arg1)
    {
        ui->send_textEdit->clear();
        ui->send_textEdit->append("hello server");
    }
    else        // 选择框被选中，则当前为hex模式，设置默认显示内容
    {
        ui->send_textEdit->clear();
        ui->send_textEdit->append("AA BB");
    }
}
