#include "logtest.h"
#include "easylogging++.h"

#include <iostream>

using namespace std;

INITIALIZE_EASYLOGGINGPP

void logtest()
{
    cout<<"logtest"<<endl;

    el::Configurations conf("log.conf");
    el::Loggers::reconfigureAllLoggers(conf);

    int a = 100;

//    LOG(TRACE)   << "***** trace log  *****"<<true;
    LOG(DEBUG)   << "***** debug log  *****"<<true<<":"<<a;
//    LOG(ERROR)   << "***** error log  *****";
//    LOG(WARNING) << "***** warning log  *****";
//    LOG(INFO)    << "***** info log  *****";

}




