#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSerialPortInfo>
#include <QTimer>
#include <QDebug>
#include <QThread>

#include "modbus.h"

#define M1   0x00
#define M2   0x10

#define SETANG 0x01 //设置角度
#define MOVE   0x02 //点动模式
#define FWD  0x01
#define REV  0x10

#define SETPREPOS   0x06   //设置原始点
#define MAXPOS      0xa5   //最大极限
#define MINPOS      0x5a   //最小极限

#define SETSPEED 0x03 //设置速度

#define GETANGLE    0x04   //获取角度

#define RSTEST  0xaa //测试用模式


#define LEFT  M2
#define RIGHT M1

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void reflashConfigBox();
    void reflashPortList();

    void releaseSerialModbus();
    static void stBusMonitorRawData(modbus_t *modbus, uint8_t *data, uint8_t dataLen, uint8_t addNewline);

    void connectedstateChange();

    void setMotorAng(char motornumber, qint16 ang);
    
    void sendCMD(char motornumber, qint8 cmd, qint16 para, qint8 expara=0x00);
    void sendByteCMD(char motornumber, qint8 cmd, qint8 para1,qint8 para2, qint8 expara=0x00);    
    void sendByteCMD(qint8 cmd, qint8 para1, qint8 para2, qint8 expara=0x00);

    void readRAWData(QByteArray &rb);

private slots:
    void on_pbConnect_clicked();

    void on_hsLeft_sliderReleased();

    void on_sbLeft_editingFinished();

    void on_hsRight_sliderReleased();

    void on_sbRight_editingFinished();

    void on_pbClearLog_clicked();
    void on_pbSendRaw_clicked();

    void on_leRawSend_editingFinished();

    void on_pbLeftUp_clicked();

    void on_pbLeftDown_clicked();

    void on_pbRightUp_clicked();

    void on_pbRightDown_clicked();

    void on_pbLeftSet0_clicked();

    void on_pbLeftSetMax_clicked();

    void on_pbRightSet0_clicked();

    void on_pbRightSetMax_clicked();

    void on_pbSendTest_clicked();

    void timerHandle();
    void on_pbSendSpeed_clicked();

    void on_pbLeftGetAngle_clicked();

    void on_pbRightGetAngle_clicked();

private:
    Ui::MainWindow *ui;
    modbus_t *mb;
    bool m_connected;
    char ConvertHexChar(char ch);
    QByteArray GetHexValue(QString str);
    QTimer *timer;
};

#endif // MAINWINDOW_H
