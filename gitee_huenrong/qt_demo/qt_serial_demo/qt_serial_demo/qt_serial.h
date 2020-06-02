#ifndef QT_SERIAL_H
#define QT_SERIAL_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class qt_serial;
}

class qt_serial : public QWidget
{
    Q_OBJECT

public:
    explicit qt_serial(QWidget *parent = nullptr);
    ~qt_serial();

private slots:
    void on_clear_windows_pushButton_clicked();

    void on_clear_send_pushButton_clicked();

    void on_open_pushButton_toggled(bool checked);

    void on_send_pushButton_clicked();

    void on_pushButton_clicked();

    void on_baud_rate_comboBox_activated(const QString &arg1);

    void on_serial_comboBox_activated(const QString &arg1);

    // 自己手动添加的槽函数
    // 读取数据槽函数
    void slot_read_data(void);

    void on_send_textEdit_textChanged();

    void on_hex_checkBox_stateChanged(int arg1);

private:
    Ui::qt_serial *ui;
    QSerialPort *serial;     // 串口实例
    qint32 serial_baud_rate;        // 记录选择的波特率

private:
    /************************************************************************
    函数名称: init_serial
    函数功能: 初始化串口(获取本机所有串口)
    函数参数: 无
    函数返回: 无
    ************************************************************************/
    void init_serial(void);
};

#endif // QT_SERIAL_H
