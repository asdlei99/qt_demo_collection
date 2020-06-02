#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QMessageBox>
#include "stdafx.h"
#include <stdio.h>
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

// void configure_defaults(CEmergentCamera* camera);
// char* next_token;

int main(int argc, char *argv[])
{
  CEmergentCamera camera;
  
  QApplication a(argc, argv);
    MainWindow w;
    w.showNormal();
/*  QPushButton quit;
    quit.setText("Quit");
    QObject::connect(&quit, SIGNAL (clicked()), &a, SLOT (quit()));
    quit.show();
*/
    //connect(q_button,SIGNAL(clicked()),q,SLOT(quit()));
    return a.exec();
}

// void configure_defaults(CEmergentCamera* camera)
// {
//   unsigned int width_max, height_max, param_val_max;
//   const unsigned long enumBufferSize = 1000;
//   unsigned long enumBufferSizeReturn = 0;
//   char enumBuffer[enumBufferSize];
// 
//   //Order is important as param max/mins get updated.
//   EVT_CameraGetEnumParamRange(camera, "PixelFormat", enumBuffer, enumBufferSize, &enumBufferSizeReturn);
//   char* enumMember = strtok_s(enumBuffer, ",", &next_token);
//   EVT_CameraSetEnumParam(camera,      "PixelFormat", enumMember);
// 
//   EVT_CameraSetUInt32Param(camera,    "FrameRate", 60);
// 
//   EVT_CameraSetUInt32Param(camera,    "OffsetX", 0);
//   EVT_CameraSetUInt32Param(camera,    "OffsetY", 0);
// 
//   EVT_CameraGetUInt32ParamMax(camera, "Width", &width_max);
//   EVT_CameraSetUInt32Param(camera,    "Width", width_max);
// 
//   EVT_CameraGetUInt32ParamMax(camera, "Height", &height_max);
//   EVT_CameraSetUInt32Param(camera,    "Height", height_max);
// 
//   EVT_CameraSetEnumParam(camera,      "AcquisitionMode",        "Continuous");
//   EVT_CameraSetUInt32Param(camera,    "AcquisitionFrameCount",  1);
//   EVT_CameraSetEnumParam(camera,      "TriggerSelector",        "AcquisitionStart");
//   EVT_CameraSetEnumParam(camera,      "TriggerMode",            "Off");
//   EVT_CameraSetEnumParam(camera,      "TriggerSource",          "Software");
//   EVT_CameraSetEnumParam(camera,      "BufferMode",             "Off");
//   EVT_CameraSetUInt32Param(camera,    "BufferNum",              0);
// 
//   EVT_CameraGetUInt32ParamMax(camera, "GevSCPSPacketSize", &param_val_max);
//   EVT_CameraSetUInt32Param(camera,    "GevSCPSPacketSize", param_val_max);
// 
//   EVT_CameraSetUInt32Param(camera,    "Gain", 256);
//   EVT_CameraSetUInt32Param(camera,    "Offset", 0);
// 
//   EVT_CameraSetBoolParam(camera,      "LUTEnable", false);
//   EVT_CameraSetBoolParam(camera,      "AutoGain", false);
// }