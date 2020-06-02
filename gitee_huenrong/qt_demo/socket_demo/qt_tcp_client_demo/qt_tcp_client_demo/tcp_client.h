#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class tcp_client;
}

class tcp_client : public QWidget
{
    Q_OBJECT

public:
    explicit tcp_client(QWidget *parent = nullptr);
    ~tcp_client();

private slots:
    void on_link_pushButton_toggled(bool checked);

    void on_send_pushButton_clicked();

    void on_clear_send_pushButton_clicked();

    void on_clear_windows_pushButton_clicked();

    // 自己添加的私有槽函数

    // 有数据需要读取的槽函数
    void slot_read_data(void);

    void on_send_textEdit_textChanged();

    void on_hex_checkBox_stateChanged(int arg1);

private:
    Ui::tcp_client *ui;
    QTcpSocket *user_tcp_client;
};

#endif // TCP_CLIENT_H
