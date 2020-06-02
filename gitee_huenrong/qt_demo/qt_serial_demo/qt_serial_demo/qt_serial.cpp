#include "qt_serial.h"
#include "ui_qt_serial.h"
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QInputDialog>

qt_serial::qt_serial(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qt_serial)
{
    ui->setupUi(this);

    serial = new QSerialPort();

    init_serial();      // 获取本机串口并显示到下拉菜单

    // 获取当前界面默认波特率
    serial_baud_rate = ui->baud_rate_comboBox->currentText().toInt();

    // 关联读取数据槽函数
    connect(serial, SIGNAL(readyRead()), this, SLOT(slot_read_data()));
}

qt_serial::~qt_serial()
{
    delete ui;
}

/************************************************************************
函数名称: init_serial
函数功能: 初始化串口(获取本机所有串口)
函数参数: 无
函数返回: 无
************************************************************************/
void qt_serial::init_serial(void)
{
    // 获取本机所有串口
    QList<QSerialPortInfo> serial_infos = QSerialPortInfo::availablePorts();

    // 本机没有串口
    if (serial_infos.isEmpty())
    {
        ui->serial_comboBox->addItem("无串口");
    }
    else        // 扫描到本机串口, 则显示出来
    {
        foreach(QSerialPortInfo serial_info, serial_infos)
        {
            ui->serial_comboBox->addItem(serial_info.portName());
            // qDebug() << "serial_port_name: " << serial_info.portName();
        }
    }
}

// 读取数据槽函数
void qt_serial::slot_read_data(void)
{
    QString show_data;

    // 如果有数据需要读取
    if (serial->bytesAvailable())
    {
        // 读取数据
        QByteArray read_data = serial->readAll();

        // 如果hex复选框被选中，则需要将接收数据转换成hex格式
        if (ui->hex_checkBox->checkState())
        {
            // 将接收数据转换成hex，并转换成大写
            QString recv_data_hex = read_data.toHex().toUpper();

            // 在字节间插入空格
            for (int i=0; i<recv_data_hex.length(); i+=2)
            {
                show_data += recv_data_hex.mid(i, 2);
                show_data += " ";
            }
        }
        else
        {
            show_data = read_data.data();
        }

        // 读取数据不为空，则将接收数据显示到窗口
        if (!show_data.isEmpty())
        {
            ui->show_textEdit->append(QString("[%1]<-: %2").
                                      arg(QTime::currentTime().toString("hh:mm:ss.zzz")).
                                      arg(show_data));
        }
    }
}

// 清空窗口按钮
void qt_serial::on_clear_windows_pushButton_clicked()
{
    ui->show_textEdit->clear();
}

// 清空发送数据按钮
void qt_serial::on_clear_send_pushButton_clicked()
{
    ui->send_textEdit->clear();
}

// 打开串口按钮
void qt_serial::on_open_pushButton_toggled(bool checked)
{
    // 按钮被按下
    if (true == checked)
    {
        // 设置串口名
        serial->setPortName(ui->serial_comboBox->currentText());
        // 设置波特率
        // serial->setBaudRate(ui->baud_rate_comboBox->currentText().toInt());
        serial->setBaudRate(serial_baud_rate);
        // 设置数据位
        serial->setDataBits(QSerialPort::Data8);
        // 设置奇偶校验位
        serial->setParity(QSerialPort::NoParity);
        // 设置停止位
        serial->setStopBits(QSerialPort::OneStop);
        // 设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);

        // 设置读取buf大小
        serial->setReadBufferSize(1024);

        // 打开串口(读写方式)
        // 打开串口成功
        if (serial->open(QIODevice::ReadWrite))
        {
            ui->open_pushButton->setText(tr("关闭串口"));
        }
        else        // 打开串口失败, 弹出提示框
        {
            QMessageBox::information(this, tr("打开串口失败"),
                                     serial->errorString(), QMessageBox::Ok);
        }
    }
    else        // 按钮未被按下
    {
        // 关闭串口
        serial->close();

        // 更新按钮显示内容
        ui->open_pushButton->setText(tr("打开串口"));
    }
}

// 发送数据按钮
void qt_serial::on_send_pushButton_clicked()
{
    qint64 ret = -1;

    // 如果串口没有打开
    if (!serial->isOpen())
    {
        QMessageBox::information(this, tr("发送数据失败"),
                                 tr("串口未打开"), QMessageBox::Ok);

        return;
    }

    // 如果发送框没有数据
    if (ui->send_textEdit->toPlainText().isEmpty())
    {
        QMessageBox::information(this, tr("发送数据失败"),
                                 tr("请输入发送内容"), QMessageBox::Ok);

        return;
    }

    // 读取发送框的数据
    QString send_data = ui->send_textEdit->toPlainText();

    // 如果hex复选框被选中，则需要将数据转换成hex格式
    if (ui->hex_checkBox->checkState())
    {
        QByteArray send_data_hex = QByteArray::fromHex(send_data.toLatin1().data());

        // 发送hex数据
        ret = serial->write(send_data_hex.data(), send_data_hex.length());
    }
    else
    {
        // 发送数据
        ret = serial->write(send_data.toStdString().c_str(),
                      strlen(send_data.toStdString().c_str()));
    }

    // 发送数据
    // qint64 ret = serial->write(send_data.toStdString().c_str());

    // 发送输入成功，将输入显示到窗口
    if (-1 != ret)
    {
        ui->show_textEdit->append(QString("[%1]->: %2").
                                  arg(QTime::currentTime().toString("hh:mm:ss.zzz")).
                                  arg(send_data));
    }
}

// 刷新串口按钮
void qt_serial::on_pushButton_clicked()
{
    // 刷新串口前先清除当前下拉菜单的信息
    ui->serial_comboBox->clear();

    init_serial();      // 重新扫描本机串口
}

// 波特率下拉框
void qt_serial::on_baud_rate_comboBox_activated(const QString &arg1)
{
    bool status;

    // 如果选择“custom”项，则是要手动输入波特率
    if ("custom" == arg1)
    {
        int input_serial_baud_rate = QInputDialog::getInt(this, tr("输入波特率"),
                                                          tr("请输入波特率, 范围[110, 2000000]"),
                                                          115200, 110, 2000000, 1, &status);

        serial_baud_rate = input_serial_baud_rate;
    }
    else
    {
        serial_baud_rate = arg1.toInt();
    }

    // qDebug() << "baud rate: " << serial_baud_rate;

    // 如果当前串口处于打开状态，则更改波特率后需要重新打开串口(先关闭, 再打开)
    if (serial->isOpen())
    {
        // 关闭串口
        serial->close();

        // 再次打开串口
        // 设置串口名
        serial->setPortName(ui->serial_comboBox->currentText());
        // 设置波特率
        serial->setBaudRate(serial_baud_rate);
        // 设置数据位
        serial->setDataBits(QSerialPort::Data8);
        // 设置奇偶校验位
        serial->setParity(QSerialPort::NoParity);
        // 设置停止位
        serial->setStopBits(QSerialPort::OneStop);
        // 设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);

        // 设置读取buf大小
        serial->setReadBufferSize(1024);

        // 打开串口(读写方式)
        // 打开串口成功
        if (serial->open(QIODevice::ReadWrite))
        {
            ui->open_pushButton->setText(tr("关闭串口"));
        }
        else        // 打开串口失败, 弹出提示框
        {
            QMessageBox::information(this, tr("打开串口失败"),
                                     serial->errorString(), QMessageBox::Ok);
        }
    }

}

// 串口号下拉框
void qt_serial::on_serial_comboBox_activated(const QString &arg1)
{
    // 如果当前串口处于打开状态，则更改波特率后需要重新打开串口(先关闭, 再打开)
    if (serial->isOpen())
    {
        // 关闭串口
        serial->close();

        // 再次打开串口
        // 设置串口名
        serial->setPortName(arg1);
        // 设置波特率
        serial->setBaudRate(serial_baud_rate);
        // 设置数据位
        serial->setDataBits(QSerialPort::Data8);
        // 设置奇偶校验位
        serial->setParity(QSerialPort::NoParity);
        // 设置停止位
        serial->setStopBits(QSerialPort::OneStop);
        // 设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);

        // 设置读取buf大小
        serial->setReadBufferSize(1024);

        // 打开串口(读写方式)
        // 打开串口成功
        if (serial->open(QIODevice::ReadWrite))
        {
            ui->open_pushButton->setText(tr("关闭串口"));
        }
        else        // 打开串口失败, 弹出提示框
        {
            QMessageBox::information(this, tr("打开串口失败"),
                                     serial->errorString(), QMessageBox::Ok);
        }
    }
}

// 输入框内容改变
void qt_serial::on_send_textEdit_textChanged()
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
void qt_serial::on_hex_checkBox_stateChanged(int arg1)
{
    // 选择框未选中，则当前为字符串模式，设置默认显示内容
    if (0 == arg1)
    {
        ui->send_textEdit->clear();
        ui->send_textEdit->append("hello serial");
    }
    else        // 选择框被选中，则当前为hex模式，设置默认显示内容
    {
        ui->send_textEdit->clear();
        ui->send_textEdit->append("AA BB");
    }
}
