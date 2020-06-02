#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextCursor>

namespace Ui {
class tcp_server;
}

class tcp_server : public QWidget
{
    Q_OBJECT

public:
    explicit tcp_server(QWidget *parent = nullptr);
    ~tcp_server();

private slots:
    void on_listen_pushButton_toggled(bool checked);

    // 自己添加的私有槽函数
    // 接收一个新连接产生的槽函数
    void slot_new_connection(void);

    // 有数据需要读取的槽函数
    void slot_read_data(void);

    void on_send_pushButton_clicked();

    void on_clear_windows_pushButton_clicked();

    void on_clear_send_pushButton_clicked();

    void on_send_textEdit_textChanged();

    void on_hex_checkBox_stateChanged(int arg1);

private:
    Ui::tcp_server *ui;
    QTcpServer *user_tcp_server;
    QTcpSocket *user_tcp_socket;
    QTextCursor last_cursor;        // 记录上一次发送框中光标位置

private:
    /************************************************************************
    函数名称: get_local_ip
    函数功能: 获取本机ip地址
    函数参数: 无
    函数返回: 无
    ************************************************************************/
    void get_local_ip(void);

    /************************************************************************
    函数名称: init_tcp_server
    函数功能: 初始化tcp服务器
    函数参数: 无
    函数返回: 成功: true
              失败: false
    ************************************************************************/
    bool init_tcp_server(void);
};

#endif // TCP_SERVER_H
