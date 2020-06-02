#include "connector.h"

#include <QElapsedTimer>
#include <QTimerEvent>
#include <qfile.h>
#include <qtextstream.h>

#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

//typedef unsigned char uchar;
//typedef unsigned short ushort;
//usb
const int CtVid = 0x8888;
const int CtPid = 0x88;

const unsigned char CtBuklRecvEP = 0x82;
const unsigned char CtBulkSendEP = 0x02;
const unsigned char CtIntRevEp = 0x81;
const unsigned char CtIntSendEp = 0x01;
//
const int CtTimerIntervalms = 10;
const int CtRecvBuffSize = 5000;

uchar GRevFrameBuff[CtRecvBuffSize];
//
Connector::Connector(QObject *parent) : QObject(parent)
{
    m_dev_handle = NULL;

    m_readId = startTimer(CtTimerIntervalms);
    m_writeId = startTimer(100);

    cout<<"id:"<<m_readId<<"|"<<m_writeId<<endl;

    //    QElapsedTimer et;
    //    et.start();
    //    while(et.elapsed() < 100);

    open();
    write();
    //    printUsbDev();
}

Connector::~Connector()
{
    libusb_release_interface(m_dev_handle,0);
    libusb_close(m_dev_handle);
    libusb_exit(NULL);
}

void Connector::open()
{
    libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    //    libusb_device_handle *dev_handle=NULL; //a device handle
    libusb_context *ctx = NULL; //a libusb session
    int r; //for return values
    ssize_t cnt; //holding number of devices in list
    //1.初始化usb设备
    r = libusb_init(&ctx); //initialize the library for the session we just declared
    if(r < 0) {
        perror("Init Error\n"); //there was an error
        //            return 1;
    }

#if 1
    //2.根据vid,pid查找设备
    m_dev_handle = libusb_open_device_with_vid_pid(ctx,CtVid,CtPid);
    if(m_dev_handle == NULL){
        printf("dev_handle is NULL\n");
        return;
    }else{
        printf("dev_handle got\n");
    }
#endif

    //3.确定指定接口的内核驱动是否激活
    int actual; //used to find out how many bytes were written
    if(libusb_kernel_driver_active(m_dev_handle, 0) == 1) { //find out if kernel driver is attached
        cout<<"Kernel Driver Active"<<endl;
        if(libusb_detach_kernel_driver(m_dev_handle, 0) == 0) //detach it
            cout<<"Kernel Driver Detached!"<<endl;
    }
    //4.为指定设备接口申请接口
    r = libusb_claim_interface(m_dev_handle, 0); //claim interface 0 (the first) of device (mine had jsut 1)
    if(r < 0) {
        cout<<"Cannot Claim Interface"<<endl;
        return;
    }

    //5.关闭接口
    //    libusb_close(m_dev_handle);
    //    libusb_exit(NULL);
}

void Connector::write()
{
    cout<<"write"<<endl;
    //write
    //    char *buf = "AA0406000055";
    //    int num = strlen(buf);

    unsigned char buf[6] = "0";
    buf[0] = 0xAA;
    buf[1] = 0x04;
    buf[2] = 0x06;
    buf[3] = 0x00;
    buf[4] = 0x00;
    buf[5] = 0x55;

    int num = 6;
    int size = 0;
    int rec = libusb_bulk_transfer(
                m_dev_handle, 0x02, buf, num, &size, 100);
    if(rec == 0) {
        printf("bulk send sucess,length: %d bytes\n", size);
    }else{
        printf("usb write falied,%s\n",libusb_error_name(rec));
    }
    cout<<"write end."<<endl;
    //    int r = libusb_release_interface(m_dev_handle, 0); //release the claimed interface
    //    if(r<0)    {
    //        printf("release interface failed\n");
    //        printError(r);
    //    }
}

void Connector::read()
{
    cout<<"read"<<endl;

    int i=0;
    //    int size;
    int rec;
    int save_bytes;
    uchar hex_buf[CtRecvBuffSize * 5] = "0";

    //rec = libusb_bulk_transfer(
    //          m_dev_handle, BULK_RECV_EP, rev_buf, RECV_BUFF_LEN, &size, 0);
    memset(GRevFrameBuff,0,CtRecvBuffSize);
    rec = libusb_bulk_transfer(
                m_dev_handle, 0x81, GRevFrameBuff, CtRecvBuffSize,
                (int*)&m_revFrameSize, 100);
    if(rec == 0){
        printf("bulk read succ,data size:%d\n",m_revFrameSize);

        hex2str(hex_buf,GRevFrameBuff,(ushort)m_revFrameSize);
        printf("data is :%s\n",hex_buf);
        cout<<endl;

        dataParser();
        return;
    }else{
        printf("bulk read failed\n");
        printError(rec);
    }

    fflush(stdout);
    //        char data = hex_buf[0];
    //        printf("data:0x%x\n",hex_buf[0]);
    //        printf("data:0x%x\n",hex_buf[1000]);
}

void Connector::printUsbDev()
{
#if 1
    libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    libusb_device_handle *dev_handle=NULL; //a device handle
    libusb_context *ctx = NULL; //a libusb session
    int r; //for return values
    ssize_t cnt; //holding number of devices in list
    r = libusb_init(&ctx); //initialize the library for the session we just declared
    if(r < 0) {
        perror("Init Error\n"); //there was an error
        //            return 1;
    }
    //        libusb_set_debug(ctx, LIBUSB_LOG_LEVEL_INFO); //set verbosity level to 3, as suggested in the documentation'
    //        int LIBUSB_CALL libusb_set_option(libusb_context *ctx, enum libusb_option option, ...);
    //        libusb_set_option(ctx,LIBUSB_LOG_LEVEL_INFO);

    cnt = libusb_get_device_list(ctx, &devs); //get the list of devices
    if(cnt < 0) {
        perror("Get Device Error\n"); //there was an error
        //            return 1;
    }
    printf("%d Devices in list.\n", cnt);

    struct libusb_device *target_dev = NULL;
    for(int i = 0;i < cnt; ++i){
        //    int LIBUSB_CALL libusb_get_device_descriptor(libusb_device *dev,
        //        struct libusb_device_descriptor *desc);
        struct libusb_device_descriptor desc ;
        if(0 < libusb_get_device_descriptor(*devs,&desc)){
            printf("libusb_get dev descriptor,failed\n");
        }

        //                        printf("length:%d\n",desc.bLength);
        //                        printf("\tCLASS(0x%x) SUBCLASS(0x%x) PROTOCOL(0x%x)\n",
        //                               desc.bDeviceClass, desc.bDeviceSubClass, desc.bDeviceProtocol);

        printf("\tVENDOR(0x%x) PRODUCT(0x%x)\n", desc.idVendor, desc.idProduct);


        //        if((desc.idVendor == ConVid) && (desc.idProduct == ConPid)){
        //            printf("get target dev\n");
        //            target_dev = *devs;
        //            break;
        //        }

        devs++;
    }

    fflush(stdout);
#if 0
    int ret = libusb_open(target_dev, &dev_handle);
    if (dev_handle == NULL)
    {
        printf("open device error:%d\n", ret);
        //    return ret;
    }else{
        printf("open device ok.\n");
    }
#endif
    //#if 0
    //    //libusb规定在用设备操作符发送数据前，需设置usb设备的配置模式和接口
    //    if ((r=libusb_set_configuration(udev, 1)) < 0) {  //设置usb设备配置模式为1
    //        qDebug("error setting config #1: %s",  libusb_error_name(r));
    //        exit(1);
    //    }
    //    if ((r=libusb_claim_interface(udev, 0)) < 0) {   //设置usb设备接口为0
    //        qDebug("error claiming interface #0:\n%s", libusb_error_name(r));
    //        exit(1);

    //#endif


    libusb_close(dev_handle);
    libusb_exit(ctx);
#endif

}

void Connector::printError(const int num)
{
    //    printf("failed,%d:%s\n",num,libusb_error_name(num));
    cout<<"failed,num:"<<num<<","<<libusb_error_name(num)<<endl;
}

void Connector::reset()
{
    if(m_dev_handle != NULL){
        int re =  libusb_reset_device(m_dev_handle);
        if(re < 0){
            printError(re);
        }
    }
}

void Connector::printdev(libusb_device *dev)
{
    libusb_device_descriptor desc;
    int r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0) {
        cout<<"failed to get device descriptor"<<endl;
        return;
    }
    cout<<"Number of possible configurations: "<<(int)desc.bNumConfigurations<<"  ";
    cout<<"Device Class: "<<(int)desc.bDeviceClass<<"  ";
    cout<<"VendorID: "<<desc.idVendor<<"  ";
    cout<<"ProductID: "<<desc.idProduct<<endl;
    libusb_config_descriptor *config;
    libusb_get_config_descriptor(dev, 0, &config);
    cout<<"Interfaces: "<<(int)config->bNumInterfaces<<" ||| ";
    const libusb_interface *inter;
    const libusb_interface_descriptor *interdesc;
    const libusb_endpoint_descriptor *epdesc;
    for(int i=0; i<(int)config->bNumInterfaces; i++) {
        inter = &config->interface[i];
        cout<<"Number of alternate settings: "<<inter->num_altsetting<<" | ";
        for(int j=0; j<inter->num_altsetting; j++) {
            interdesc = &inter->altsetting[j];
            cout<<"Interface Number: "<<(int)interdesc->bInterfaceNumber<<" | ";
            cout<<"Number of endpoints: "<<(int)interdesc->bNumEndpoints<<" | ";
            for(int k=0; k<(int)interdesc->bNumEndpoints; k++) {
                epdesc = &interdesc->endpoint[k];
                cout<<"Descriptor Type: "<<(int)epdesc->bDescriptorType<<" | ";
                cout<<"EP Address: "<<(int)epdesc->bEndpointAddress<<" | ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    cout<<endl<<endl<<endl;
    libusb_free_config_descriptor(config);
}

int Connector::str2hex(char *hex)
{
    int sum = 0;
    int tmp = 0;
    char hex_str[5];

    if(strlen(hex) == 6)    //0x1234
        memcpy(hex_str, &hex[2], 4);
    else
        memcpy(hex_str, hex, 4);

    for(int i = 0; i < 4; i++)
    {
        tmp = hex_str[i] - (((hex_str[i] >= '0') && (hex_str[i] <= '9')) ? '0' : \
                                                                           ((hex_str[i] >= 'A') && (hex_str[i] <= 'Z')) ? 'A' - 10 : 'a' - 10);
        sum += tmp * pow(16, 3-i);
    }

    return sum;
}

void Connector::hex2str(uchar *dest, uchar *src, ushort nLen)
{
    int i;

    for (i=0; i<nLen; i++)
    {
        sprintf((char*)dest+5*i, "%#04x ", src[i]);    //string类函数，不会造成线程切换
    }

    dest[nLen*5] = '\0';
}

void Connector::dataParser()
{
    //数据实际数量
    printf("%x,%x\n",GRevFrameBuff[3],GRevFrameBuff[2]);
    int count = (GRevFrameBuff[3] << 8) + GRevFrameBuff[2];
    cout<<"dataOperate num:"<<count<<endl;
    //4581
    count = 4581;
    int offset = 4;
    vector<uint> dataVtr;
    for(int i = offset; i < count - 1; ){
        dataVtr.push_back((GRevFrameBuff[i + 1] << 8) + GRevFrameBuff[i]);
        i +=2;
    }

    uint dataFiled[44][52] = {0};

    int column = 0;
    int row = 0;

    //    for(int i = 0; i < count; ++i){
    for(auto &item:dataVtr){
        if(column == 52){
            column = 0;
            ++row;
        }

        dataFiled[row][column] = item;
        ++column;
    }



    QFile file("in.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text|QIODevice::Truncate)){
        cout<<"file open failed."<<endl;
        return;
    }
    QTextStream ts(&file);
    //    file.write()
    for(int i = 0; i < 44; ++i){
        QStringList list;
        cout<<"row:"<<i<<"--";
        for(int key = 0;key < 52; ++key){
            //                    printf("\t%d ",dataFiled[i][key]);
            QString s = QString::number(dataFiled[i][key]);
//            ts<<s<<",";
            list.append(s);
            //            file.write(s.toStdString().data(),s.size());
            cout<<s.toStdString()<<" ";
        }

        ts<<list.join(",")<<"\r";
                        cout<<endl;
    }

    file.close();

}

void Connector::timerEvent(QTimerEvent *event)
{
    static int count = 0;
    cout<<"timerevent"<<endl;
    cout<<"id:"<<event->timerId()<<endl;

    if(event->timerId() == m_writeId){
        write();
        //        killTimer(m_writeId);
    }

    if(event->timerId() == m_readId){
        if(count == 1){
            exit(0);
        }else{
            ++count;
        }

        if(m_dev_handle == NULL){
            cout<<"m dev handle is null"<<endl;
            return;
        }

        read();

    }
}


void Connector::HexToAscii(unsigned char *pHex, unsigned char *pAscii, int nLen)
{
    unsigned char Nibble[2];

    for (int i = 0; i < nLen; i++)
    {
        Nibble[0] = (pHex[i] & 0xF0) >> 4;
        Nibble[1] = pHex[i] & 0x0F;
        for (int j = 0; j < 2; j++)
        {
            if (Nibble[j] < 10)
                Nibble[j] += 0x30;
            else
            {
                if (Nibble[j] < 16)
                    Nibble[j] = Nibble[j] - 10 + 'A';
            }
            *pAscii++ = Nibble[j];
        }   // for (int j = ...)
    }   // for (int i = ...)
}



