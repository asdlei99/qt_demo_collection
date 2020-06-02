#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    reflashPortList();

    reflashConfigBox();

    m_connected = false;
    mb = NULL;

    timer = new QTimer();
    timer->setInterval(500);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerHandle()));
    connectedstateChange();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reflashPortList()
{
    ui->cbPortList->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    QStandardItemModel *model = new QStandardItemModel();//添加提示tootip

    for (const QSerialPortInfo &info : infos) {
        if(!info.isBusy())
        {
            QStandardItem *item = new QStandardItem(info.portName());
            item->setToolTip(info.description());
            model->appendRow(item);
        }
    }
    ui->cbPortList->setModel(model);
}

void MainWindow::releaseSerialModbus()
{
    if( mb )
    {
        modbus_close( mb );
        modbus_free( mb );
        mb = NULL;
    }
}

void MainWindow::reflashConfigBox()
{
    QString str = "1200,2400,4800,9600,19200,38400,57600,115200";
    QStringList strlist = str.split(',');
    ui->cbBaudList->addItems(strlist);
    ui->cbBaudList->setCurrentIndex(7); //默认115200

    str.clear();strlist.clear();
    str = "1,1.5,2";
    strlist = str.split(',');
    ui->cbStopList->addItems(strlist);

    str.clear();strlist.clear();
    str = "5,6,7,8";
    strlist = str.split(',');
    ui->cbDataBitsList->addItems(strlist);
    ui->cbDataBitsList->setCurrentIndex(3); //8bit

    str.clear();strlist.clear();
    str = "No,Even,Odd";
    strlist = str.split(',');
    ui->cbPairtyList->addItems(strlist);
}

void MainWindow::on_pbConnect_clicked()
{
    if(m_connected == false)
    {
#ifdef Q_OS_WIN32
        QString port = ui->cbPortList->currentText();

        // is it a serial port in the range COM1 .. COM9?
        if ( port.startsWith( "COM" ) )
        {
            // use windows communication device name "\\.\COMn"
            port = "\\\\.\\" + port;
        }
#else
        const QString port = ui->cbPortList->currentText();
#endif

        char parity  = ui->cbPairtyList->currentText().at(0).toLatin1();
        int baud = ui->cbBaudList->currentText().toInt();
        int databits = ui->cbDataBitsList->currentText().toInt();
        int stopbits = ui->cbStopList->currentText().toInt();

        mb = modbus_new_rtu( port.toLatin1().constData(),
                             baud,parity,databits,stopbits);


        if( modbus_connect( mb ) == -1 )
        {
            releaseSerialModbus();
            return;
        }
        m_connected = true;
        connectedstateChange();
        modbus_register_monitor_raw_data_fnc(mb, MainWindow::stBusMonitorRawData);
        modbus_set_debug(mb,true);
        modbus_set_slave(mb,0x00);
        //timer->start();
    }else {
        releaseSerialModbus();
        m_connected = false;
        connectedstateChange();
        timer->stop();
    }
}


void MainWindow::on_hsLeft_sliderReleased()
{
    double tp = ui->hsLeft->value() / 10.0;
    ui->sbLeft->setValue(tp);
    ui->preSetAngLeft->setText(QString("%1°").arg(tp));
    setMotorAng(LEFT,ui->hsLeft->value());
}

void MainWindow::on_sbLeft_editingFinished()
{
    double td = ui->sbLeft->value();
    int tp = td*10;
    ui->hsLeft->setValue(tp);
    ui->preSetAngLeft->setText(QString("%1°").arg(td));
    setMotorAng(LEFT,tp);
}

void MainWindow::on_hsRight_sliderReleased()
{
    double tp = ui->hsRight->value() / 10.0;
    ui->sbRight->setValue(tp);
    ui->preSetAngRight->setText(QString("%1°").arg(tp));
    setMotorAng(RIGHT,ui->hsRight->value());
}

void MainWindow::on_sbRight_editingFinished()
{
    double td = ui->sbRight->value();
    int tp = td*10;
    ui->hsRight->setValue(tp);
    ui->preSetAngRight->setText(QString("%1°").arg(td));
    setMotorAng(RIGHT,tp);
}

void MainWindow::on_pbClearLog_clicked()
{
    ui->teLog->clear();
}

void MainWindow::on_pbSendRaw_clicked()
{
    QString raw = ui->leRawSend->text();

    QByteArray hexdata = GetHexValue(raw);
    modbus_send_raw_request(mb,(uint8_t*)hexdata.data(),hexdata.size());
}

void MainWindow::on_leRawSend_editingFinished()
{
    QString tp = ui->leRawSend->text();
    QByteArray hexdata = GetHexValue(tp);
    ui->leRawSend->setText(hexdata.toHex());

}

// static
void MainWindow::stBusMonitorRawData( modbus_t * modbus, uint8_t * data, uint8_t dataLen, uint8_t addNewline )
{
    Q_UNUSED(modbus);
    qDebug() << data << dataLen << addNewline;
}

QByteArray MainWindow::GetHexValue(QString str)
{
    QByteArray senddata;
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}

char MainWindow::ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else return (-1);
}

void MainWindow::connectedstateChange()
{
    if(m_connected == false)
    {
        ui->gbLeft->setDisabled(true);
        ui->gbRight->setDisabled(true);
        ui->leRawSend->setDisabled(true);
        ui->pbSendRaw->setDisabled(true);

        ui->cbBaudList->setEnabled(true);
        ui->cbPairtyList->setEnabled(true);
        ui->cbPortList->setEnabled(true);
        ui->cbDataBitsList->setEnabled(true);
        ui->cbStopList->setEnabled(true);
        ui->pbConnect->setText("打开串口");
        ui->statusBar->showMessage("请先配置并打开串口");
    }else
    {
        QString ts;
        ts.append(ui->cbPortList->currentText());
        ts.append(" | ");
        ts.append(ui->cbBaudList->currentText());
        ts.append(" | ");
        ts.append(ui->cbDataBitsList->currentText());
        ts.append(" | ");
        ts.append(ui->cbStopList->currentText());
        ts.append(" | ");
        ts.append(ui->cbPairtyList->currentText());

        ui->statusBar->showMessage(ts);
        ui->gbLeft->setEnabled(true);
        ui->gbRight->setEnabled(true);
        ui->leRawSend->setEnabled(true);
        ui->pbSendRaw->setEnabled(true);

        ui->cbBaudList->setDisabled(true);
        ui->cbPairtyList->setDisabled(true);
        ui->cbPortList->setDisabled(true);
        ui->cbDataBitsList->setDisabled(true);
        ui->cbStopList->setDisabled(true);
        ui->pbConnect->setText("关闭串口");
    }
}

void MainWindow::sendCMD(char motornumber, qint8 cmd,qint16 para, qint8 expara)
{
    QByteArray buf;
    buf.append(0x55);
    buf.append(motornumber|cmd);
    buf.append(MODBUS_GET_HIGH_BYTE(para));
    buf.append(MODBUS_GET_LOW_BYTE(para));
    buf.append((char)expara);//扩展参数
    modbus_send_raw_request(mb,(uint8_t*)buf.data(),buf.size());
}

void MainWindow::sendByteCMD(char motornumber, qint8 cmd, qint8 para1, qint8 para2, qint8 expara)
{
    QByteArray buf;
    buf.append(0x55);
    buf.append(motornumber|cmd);
    buf.append(para1);
    buf.append(para2);
    buf.append((char)expara);//扩展参数
    modbus_send_raw_request(mb,(uint8_t*)buf.data(),buf.size());
}

void MainWindow::sendByteCMD(qint8 cmd, qint8 para1, qint8 para2, qint8 expara)
{
    QByteArray buf;
    buf.append(0x55);
    buf.append(cmd);
    buf.append(para1);
    buf.append(para2);
    buf.append((char)expara);//扩展参数
    modbus_send_raw_request(mb,(uint8_t*)buf.data(),buf.size());
}

void MainWindow::readRAWData(QByteArray &rb)
{
    QByteArray buf;
    buf.resize(MODBUS_RTU_MAX_ADU_LENGTH);
    int len = _receive_msg_raw(mb,(uint8_t*)buf.data());
    if(len > 0)
    {
        buf.resize(len);
        rb.append(buf);
    }
}

void MainWindow::setMotorAng(char motornumber, qint16 ang)
{
    sendCMD(motornumber,SETANG,ang);
}

void MainWindow::on_pbLeftUp_clicked()
{
    sendCMD(LEFT, MOVE ,FWD);
}

void MainWindow::on_pbLeftDown_clicked()
{
    sendCMD(LEFT, MOVE ,REV);
}

void MainWindow::on_pbRightUp_clicked()
{
    sendCMD(RIGHT, MOVE ,FWD);
}

void MainWindow::on_pbRightDown_clicked()
{
    sendCMD(RIGHT, MOVE ,REV);
}


void MainWindow::on_pbLeftSet0_clicked()
{
    sendCMD(LEFT, SETPREPOS ,MINPOS);
}

void MainWindow::on_pbLeftSetMax_clicked()
{
    sendCMD(LEFT, SETPREPOS ,MAXPOS);
}

void MainWindow::on_pbRightSet0_clicked()
{
    sendCMD(RIGHT, SETPREPOS ,MINPOS);
}

void MainWindow::on_pbRightSetMax_clicked()
{
    sendCMD(RIGHT, SETPREPOS ,MAXPOS);
}

void MainWindow::on_pbSendTest_clicked()
{
    quint16 p1 = ui->leStepTest->text().toInt();
    qint8 p2 = ui->rb_FWD->isChecked() ? FWD : REV;

    sendCMD(0,RSTEST,p1,p2);
}

void MainWindow::timerHandle()
{
    QByteArray rb;
    readRAWData(rb);

    if(rb.length())
    {
        ui->teLog->appendPlainText(rb.toHex());
    }
}

void MainWindow::on_pbSendSpeed_clicked()
{
    qint8 num = ui->spb_motornum->value();
    qint16 speed = ui->spb_speed->value();
    if(num == 1)
        sendCMD(LEFT,SETSPEED,speed);
    else if(num == 2)
        sendCMD(RIGHT,SETSPEED,speed);
}

void MainWindow::on_pbLeftGetAngle_clicked()
{
    sendCMD(LEFT, GETANGLE , 0);
    QByteArray buf;
    QThread::sleep(1);
    readRAWData(buf);
    ui->teLog->appendPlainText(buf.toHex());

    if(buf.isEmpty())
        return;
    if(buf.at(0) == 0x00 && buf.at(1) == (char)LEFT|GETANGLE)
    {
        int angle = ((uint8_t)buf.at(3))<<8;
        angle |= (uint8_t)buf.at(4);
        float fangle = angle/10.0;
        ui->teLog->appendPlainText("当前左边角度：");
        ui->teLog->appendPlainText(QString::number(fangle));
    }
}

void MainWindow::on_pbRightGetAngle_clicked()
{
    sendCMD(RIGHT, GETANGLE , 0);
    QByteArray buf;
    QThread::sleep(1);
    readRAWData(buf);
    ui->teLog->appendPlainText(buf.toHex());

    if(buf.isEmpty())
        return;
    if(buf.at(0) == 0x00 && buf.at(1) == (char)RIGHT|GETANGLE)
    {
        int angle = ((uint8_t)buf.at(3))<<8;
        angle |= (uint8_t)buf.at(4);
        float fangle = angle/10.0;
        ui->teLog->appendPlainText("当前右边角度：");
        ui->teLog->appendPlainText(QString::number(fangle));
    }
}
