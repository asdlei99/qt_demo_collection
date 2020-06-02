#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_btn_uart_Ctrl_clicked();
    void on_btn_led1_Ctrl_clicked();
    void on_btn_led2_Ctrl_clicked();
    void on_btn_clear_clicked();
    void on_cbb_baud_currentIndexChanged(const QString &arg1);
    void on_btn_serch_clicked();
    void serialPort_readyRead();        //connect连接方式，串口接收的数据进行处理
    void on_btn_send_clicked();

private:
    Ui::Dialog *ui;

    QSerialPort serial;

};

#endif // DIALOG_H
