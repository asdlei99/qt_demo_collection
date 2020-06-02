#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <QWidget>
#include <QtNetwork>

namespace Ui {
class udp_server;
}
class QUdpSocket;

class udp_server : public QWidget
{
    Q_OBJECT

public:
    explicit udp_server(QWidget *parent = nullptr);
    ~udp_server();

private:
    Ui::udp_server *ui;
    QUdpSocket *user_udp_socket;
    QHostAddress client_ip;     // 客户端的ip地址
    quint16 client_port;        // 客户端的端口号

private slots:

    // 自己添加的私有槽函数
    // 有数据需要读取的槽函数
    void slot_read_data(void);

    void on_listen_pushButton_toggled(bool checked);

    void on_send_pushButton_clicked();

    void on_clear_windows_pushButton_clicked();

    void on_clear_send_pushButton_clicked();

    void on_send_textEdit_textChanged();

    void on_hex_checkBox_stateChanged(int arg1);

private:
    /************************************************************************
    函数名称: get_local_ip
    函数功能: 获取本机ip地址
    函数参数: 无
    函数返回: 无
    ************************************************************************/
    void get_local_ip(void);

    /************************************************************************
    函数名称: init_udp_server
    函数功能: 初始化udp服务器
    函数参数: 无
    函数返回: 成功: true
              失败: false
    ************************************************************************/
    bool init_udp_server(void);
};

#endif // UDP_SERVER_H
