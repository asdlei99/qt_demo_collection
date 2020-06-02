#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QTextCodec>   //中文支持
#include <QDir>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    /*********************/
    this->setWindowTitle("串口控制LED - By wcc ");
    connect(&serial, & QSerialPort::readyRead, this, &Dialog::serialPort_readyRead);

    ui->cbb_com->clear();
    //运行开始查找可用串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->cbb_com->addItem(info.portName());  //串口号下拉菜单，增加一个条目，为串口号COM4
        qDebug() << "串口搜索完成";
    }
    ui->cbb_baud->insertItem(0, "9600");
    ui->cbb_baud->insertItem(1, "115200");
    ui->cbb_baud->insertItem(2, "3000000");
    ui->cbb_baud->insertItem(3, "自定义");
    //初始化按钮失能
    this->ui->btn_led1_Ctrl->setDisabled(true); //LED控制不可用
    this->ui->btn_led2_Ctrl->setDisabled(true);
    this->ui->btn_send->setDisabled(true);
    this->ui->te_tx_buf->setDisabled(true);
    this->ui->tb_rx_buf->document()->setMaximumBlockCount(10);//设置显示框最大行数为10行

    qDebug() << QDir::currentPath();
}

Dialog::~Dialog()
{
    delete ui;
}

//打开串口按钮
void Dialog::on_btn_uart_Ctrl_clicked()
{
    if(this->ui->btn_uart_Ctrl->text() == "打开串口")   //初始状态，配置串口参数
    {
        serial.setPortName(ui->cbb_com->currentText());     //设置串口号、
        serial.setBaudRate(ui->cbb_baud->currentText().toInt());    //设置波特率
        serial.setDataBits(QSerialPort::Data8);     //设置串口数据位8
        serial.setParity(QSerialPort::NoParity);    //无校验位
        serial.setStopBits(QSerialPort::OneStop);   //1位停止位
        serial.setFlowControl(QSerialPort::NoFlowControl);
        //打开串口
        if(!serial.open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(NULL, "提示", "串口打开失败");
            return;
        }
        qDebug() << "串口打开成功";
        this->ui->btn_uart_Ctrl->setText("关闭串口");

        this->ui->btn_led1_Ctrl->setEnabled(true);
        this->ui->btn_led2_Ctrl->setEnabled(true);
        this->ui->btn_send->setEnabled(true);
        this->ui->te_tx_buf->setEnabled(true);
    }
    else
    {
        //关闭串口
        serial.close();
        this->ui->btn_uart_Ctrl->setText("打开串口");

        this->ui->btn_led1_Ctrl->setDisabled(true); //LED控制不可用
        this->ui->btn_led2_Ctrl->setDisabled(true);
        this->ui->btn_send->setDisabled(true);
        this->ui->te_tx_buf->setDisabled(true);
    }
}
//LED1控制按钮
void Dialog::on_btn_led1_Ctrl_clicked()
{
    QPalette colr;
    if(this->ui->btn_led1_Ctrl->text() == "点亮")
    {
        colr.setColor(QPalette::WindowText,Qt::red);    //设置标签颜色红色
        this->ui->lbe_red->setPalette(colr);
        this->ui->btn_led1_Ctrl->setText("熄灭");
        serial.write("A1\n");     //串口发送A1
    }
    else
    {
        colr.setColor(QPalette::WindowText,Qt::black);
        this->ui->lbe_red->setPalette(colr);        //设置标签颜色红色
        this->ui->btn_led1_Ctrl->setText("点亮");
        serial.write("A2\n");     //串口发送A2
    }
}
//LED2控制按钮
void Dialog::on_btn_led2_Ctrl_clicked()
{
    QPalette colr;
    if(this->ui->btn_led2_Ctrl->text() == "点亮")
    {
        colr.setColor(QPalette::WindowText,Qt::blue);
        this->ui->lbe_blue->setPalette(colr);
        this->ui->btn_led2_Ctrl->setText("熄灭");
        serial.write("B1\n");     //把数据通过串口发送出去
    }
    else
    {
        colr.setColor(QPalette::WindowText,Qt::black);
        this->ui->lbe_blue->setPalette(colr);
        this->ui->btn_led2_Ctrl->setText("点亮");
        serial.write("B2\n");     //把数据通过串口发送出去
    }
}
//串口数据接收并显示
void Dialog::serialPort_readyRead()
{
    QByteArray rx_buf= serial.readAll();;
    //    if(rx_buf.endsWith("\r\n")) //判断接收最后是否是回车换行，即接收完成标志
    QString rx_buf_tmp = QString::fromLocal8Bit(rx_buf);    //转换为中文格式

    qDebug() << rx_buf_tmp;         //控制台输出
    ui->tb_rx_buf->insertPlainText(rx_buf_tmp); //追加显示，末尾不会添加
    rx_buf_tmp.clear();
    rx_buf.clear();
}
//清除接收窗口按钮
void Dialog::on_btn_clear_clicked()
{
    this->ui->tb_rx_buf->clear();
}
//自定义波特率
void Dialog::on_cbb_baud_currentIndexChanged(const QString &arg1)
{
    if(this->ui->cbb_baud->currentIndex() == 3)
    {
        this->ui->cbb_baud->setItemText(3, ""); //调成自定义波特率时，内容设置为空，准备接收输入
        this->ui->cbb_baud->setEditable(true);
    }
    else
    {
        this->ui->cbb_baud->setItemText(3, "自定义"); //调成自定义波特率时，内容设置为空，准备接收输入
        this->ui->cbb_baud->setEditable(false);
    }
    serial.setBaudRate(ui->cbb_baud->currentText().toInt());    //即使打开串口后，仍然可以设置波特率
}
//搜索串口功能
void Dialog::on_btn_serch_clicked()
{
    ui->cbb_com->clear();
    //运行开始查找可用串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->cbb_com->addItem(info.portName());  //串口号下拉菜单，增加一个条目，为串口号COM4
        qDebug() << "串口搜索完成";
    }
}
//发送按钮被按下
void Dialog::on_btn_send_clicked()
{
    QString tx_buf = ui->te_tx_buf->toPlainText();  //文本输入框的内容
    //获取多行输入框的数据并转换为UTF8格式
    QByteArray tx_buf_tmp = tx_buf.toLocal8Bit();   //转换为标准字符，支持中文

    if(ui->cb_send_enter->isChecked())
        tx_buf += "\n";

    serial.write(tx_buf_tmp);     //把数据通过串口发送出去
    tx_buf.clear();
}
