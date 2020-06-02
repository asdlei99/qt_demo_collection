#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QMessageBox>
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <EmergentCameraAPIs.h>
#include <EmergentCamera.h>
#include <EvtParamAttribute.h>
#include <gigevisiondeviceinfo.h>

using namespace std;
using namespace Emergent;

#define SUCCESS 0
//#define XML_FILE   "C:\\xml\\Emergent_HS-2000-M_1_0.xml"
#define MAX_CAMERAS 10

void configure_defaults(CEmergentCamera* camera);
char* next_token;
CEmergentCamera camera;
   
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)//,ui(new Ui::MainWindow)
{  
  m_button = new QPushButton("My Button", this);
    // set size and location of the button
    m_button->setGeometry(QRect(QPoint(20, 20), QSize(150, 70)));

    // Connect button signal to appropriate slot
    connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));

    q_button = new QPushButton("Quit",this);
    q_button->setGeometry(QRect(QPoint(180, 20), QSize(150, 70)));
//    QObject::connect(q_button, SIGNAL (clicked()), &a, SLOT (quit()));
    connect(q_button, SIGNAL (clicked()), QApplication::instance(), SLOT(quit()));

    //ui->setupUi(this);
}

void MainWindow::handleButton()
{
    // change the text
    m_button->setText("Example Button Pushed");
    // resize button
    //m_button->resize(100,100);
        
    QMessageBox msgBox;
        
    int a = 5;
    QString testMsg = "someString" + QString::number( a );
//     msgBox.setText("Example Code");
//     msgBox.exec();

    const unsigned long StringSize = 256;
    unsigned long StringSizeReturn = 0;
    char StringBuffer[StringSize];
    int ReturnVal = SUCCESS;
    struct GigEVisionDeviceInfo deviceInfo[MAX_CAMERAS];
    unsigned int count, camera_index;
    char camera_model[100];
    
    msgBox.setText("DeviceInformation : Example program  ");
//     QString text = "someString" + QString::number( a );
//     msgBox.setText("abc " + text);
    msgBox.exec();
    
      //Find all cameras in system.
  unsigned int listcam_buf_size = MAX_CAMERAS;
  EVT_ListDevices(deviceInfo, &listcam_buf_size, &count);
  if(count==0)
  {
    printf("Enumerate Cameras: \tNo cameras found. Exiting program.\n");
    //return 0;
  }

  //Find and use first EVT camera.
  for(camera_index=0; camera_index<MAX_CAMERAS;camera_index++)
  {
    strcpy_s(camera_model, deviceInfo[camera_index].modelName);
    camera_model[2] = '\0';
    if(strcmp(camera_model, "HS") == 0)
    {
      break; //Found EVT camera so break. i carries index for open.
    }

    if(strcmp(camera_model, "HT") == 0)
    {
      break; //Found EVT camera so break. i carries index for open.
    }

    if(camera_index==(MAX_CAMERAS-1))
    {
      printf("No EVT cameras found. Exiting program\n");
      //return 0;
    }
  }  

  //Open the camera. Example usage. Camera found needs to match XML.
#ifdef XML_FILE
  ReturnVal = EVT_CameraOpen(&camera, &deviceInfo[camera_index], XML_FILE);
#else
  ReturnVal = EVT_CameraOpen(&camera, &deviceInfo[camera_index]);      
#endif
  if(ReturnVal != SUCCESS)
  {
    printf("Open Camera: \t\tError. Exiting program.\n");
    //return ReturnVal;
  }
  else
  {
    printf("Open Camera: \t\tCamera Opened\n\n");
  }

  //To avoid conflict with settings in other examples.
  configure_defaults(&camera);

	//Get Device information.
	ReturnVal = EVT_CameraGetStringParam(&camera, "DeviceVendorName", StringBuffer, StringSize, &StringSizeReturn);
  if(ReturnVal != SUCCESS)
  {
    printf("EVT_CameraGetStringParam: Error\n");
    //return ReturnVal;
  }
  printf("DeviceVendorName: \t%s\n", StringBuffer);

	ReturnVal = EVT_CameraGetStringParam(&camera, "DeviceModelName", StringBuffer, StringSize, &StringSizeReturn);
  if(ReturnVal != SUCCESS)
  {
    printf("EVT_CameraGetStringParam: Error\n");
    //return ReturnVal;
  }
  printf("DeviceModelName: \t%s\n", StringBuffer);

	ReturnVal = EVT_CameraGetStringParam(&camera, "DeviceVersion", StringBuffer, StringSize, &StringSizeReturn);
  if(ReturnVal != SUCCESS)
  {
    printf("EVT_CameraGetStringParam: Error\n");
    //return ReturnVal;
  }
  printf("DeviceVersion: \t\t%s\n", StringBuffer);

	ReturnVal = EVT_CameraGetStringParam(&camera, "DeviceSerialNumber", StringBuffer, StringSize, &StringSizeReturn);
  if(ReturnVal != SUCCESS)
  {
    printf("EVT_CameraGetStringParam: Error\n");
    //return ReturnVal;
  }
  printf("DeviceSerialNumber: \t%s\n", StringBuffer);

	ReturnVal = EVT_CameraGetStringParam(&camera, "DeviceFirmwareVersion", StringBuffer, StringSize, &StringSizeReturn);
  if(ReturnVal != SUCCESS)
  {
    printf("EVT_CameraGetStringParam: Error\n");
    //return ReturnVal;
  }
  printf("DeviceFirmwareVersion: \t%s\n", StringBuffer);

  //To avoid conflict with settings in other examples.
  configure_defaults(&camera);

	//Close the camera
	EVT_CameraClose(&camera);
  printf("\nClose Camera: \t\tCamera Closed\n");

    
    
}
/*void MainWindow::quit()
{
    connect(q_button, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
}*/

MainWindow::~MainWindow()
{
//    delete ui;
}


void configure_defaults(CEmergentCamera* camera)
{
  unsigned int width_max, height_max, param_val_max;
  const unsigned long enumBufferSize = 1000;
  unsigned long enumBufferSizeReturn = 0;
  char enumBuffer[enumBufferSize];

  //Order is important as param max/mins get updated.
  EVT_CameraGetEnumParamRange(camera, "PixelFormat", enumBuffer, enumBufferSize, &enumBufferSizeReturn);
  char* enumMember = strtok_s(enumBuffer, ",", &next_token);
  EVT_CameraSetEnumParam(camera,      "PixelFormat", enumMember);

  EVT_CameraSetUInt32Param(camera,    "FrameRate", 60);

  EVT_CameraSetUInt32Param(camera,    "OffsetX", 0);
  EVT_CameraSetUInt32Param(camera,    "OffsetY", 0);

  EVT_CameraGetUInt32ParamMax(camera, "Width", &width_max);
  EVT_CameraSetUInt32Param(camera,    "Width", width_max);

  EVT_CameraGetUInt32ParamMax(camera, "Height", &height_max);
  EVT_CameraSetUInt32Param(camera,    "Height", height_max);

  EVT_CameraSetEnumParam(camera,      "AcquisitionMode",        "Continuous");
  EVT_CameraSetUInt32Param(camera,    "AcquisitionFrameCount",  1);
  EVT_CameraSetEnumParam(camera,      "TriggerSelector",        "AcquisitionStart");
  EVT_CameraSetEnumParam(camera,      "TriggerMode",            "Off");
  EVT_CameraSetEnumParam(camera,      "TriggerSource",          "Software");
  EVT_CameraSetEnumParam(camera,      "BufferMode",             "Off");
  EVT_CameraSetUInt32Param(camera,    "BufferNum",              0);

  EVT_CameraGetUInt32ParamMax(camera, "GevSCPSPacketSize", &param_val_max);
  EVT_CameraSetUInt32Param(camera,    "GevSCPSPacketSize", param_val_max);

  EVT_CameraSetUInt32Param(camera,    "Gain", 256);
  EVT_CameraSetUInt32Param(camera,    "Offset", 0);

  EVT_CameraSetBoolParam(camera,      "LUTEnable", false);
  EVT_CameraSetBoolParam(camera,      "AutoGain", false);
}

