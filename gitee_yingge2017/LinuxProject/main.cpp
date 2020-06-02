#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <thread>

#include "Cpp11/cpp11.h"
#include "Lab/lab.h"
#include "Net/net.h"
#include "process/process_test.h"
#include "sql/dbtest.h"
#include "practise/practisetest.h"
#include "log/logtest.h"

using namespace std;

//#define Cpp11
//#define Net
//#define Lab
//#define Process //多进程
//#define Db
//#define Practise
//#define Log

int main(int argc, char *argv[])
{
	cout<<"--main-------------------------------------------------------"<<endl;
    cout << "Hello World!"<<"中文" << endl;
    cout<<"[MainThread]:pid:"<<getpid()<<" tid:"<<this_thread::get_id()<<endl;

#ifdef Cpp11
    Cpp11Test();
#endif

#ifdef Net
    NetTest();
#endif

#ifdef Lab
    labTest();
#endif

#ifdef Process
    process_test();
#endif

#ifdef Db
	dbtest();
#endif

#ifdef Practise
    practisetest();
#endif

#ifdef Log
    logtest();
#endif



	cout<<"--main return----------------------------------------------------"<<endl;

    return 0;
}
