#include <QCoreApplication>
#include <qdebug.h>

#include "libmodbus/modbus.h"

void rtu(){
    qDebug()<<"rtu";
    modbus_t *mb;
    uint16_t tab_reg[32]={0};

    //创建一个RTU类型的容器
    mb = modbus_new_rtu("COM4", 57600, 'N', 8, 1);   //相同的端口只能同时打开一个
    if(mb == nullptr){
        qDebug()<<"modbus_new_rtu failed."
               <<QString::fromStdString(modbus_strerror(errno));
        return ;
    }
    //设置modbus从机地址
    modbus_set_slave(mb, 2);
    //设置debug模式
    modbus_set_debug(mb,true);
    //RTU模式下打开串口
    if(-1 == modbus_connect(mb)){
        qDebug()<<"modbus_connect failed."
               <<QString::fromStdString(modbus_strerror(errno));
        modbus_free(mb);
        return;
    }

    struct timeval t;
    t.tv_sec=0;
    t.tv_usec=1000000;   //设置modbus超时时间为1000毫秒
    //    if(-1 == modbus_set_response_timeout(mb, t.tv_sec,t.tv_usec)){
    if(-1 == modbus_set_response_timeout(mb, 0, 100000)){
        qDebug()<<"modbus_set_response_timeout failed."
               <<QString::fromStdString(modbus_strerror(errno));
        return ;
    }

    int regs=modbus_read_registers(mb, 1, 1, tab_reg);
    if(regs == -1){
        qDebug()<<"read failed."
               <<QString::fromStdString(modbus_strerror(errno));
        return ;
    }
    else{
        qDebug()<<"read secc";
    }

    for (int i=0; i < regs; i++) {
        printf("reg[%d]=%d (0x%X)\n", i, tab_reg[i], tab_reg[i]);
    }

    //       QMessageBox::about(NULL, "报告", QString("Rtu读取寄存器的个数:%1").arg(regs));
    modbus_close(mb);
    modbus_free(mb);

    return;
}
void tcp(){
    qDebug()<<"tcp";
    modbus_t *mb;
    uint16_t tab_reg[32]={0};

    mb = modbus_new_tcp("127.0.0.1", 5101);  //由于是tcp client连接，在同一个程序中相同的端口可以连接多次。
    modbus_set_slave(mb, 1);  //从机地址

    modbus_connect(mb);

    struct timeval t;
    t.tv_sec=0;
    t.tv_usec=1000000;   //设置modbus超时时间为1000毫秒，注意：经测试，如果没有成功建立tcp连接，则该设置无效。
    //        modbus_set_response_timeout(mb, &t);
    modbus_set_response_timeout(mb, t.tv_sec,t.tv_usec);

    int regs=modbus_read_registers(mb, 0, 20, tab_reg);

    //   QMessageBox::about(NULL, "报告", QString("Tcp读取寄存器的个数:%1").arg(regs));
    modbus_close(mb);
    modbus_free(mb);

}

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

    rtu();

//    return a.exec();
    return 0;
}
