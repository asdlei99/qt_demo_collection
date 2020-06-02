#include "../Cpp11/cpp11.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

using namespace std;

void Cpp11Test()
{
    //线程测试
    //    ThreadTest();
    //线程延时函数
    //    SleepTest();
    //获取当前时间与计算函数运行时间
    timeTest();
}

void ThreadTest()
{
    cout<<__func__<<"-------------------------------"<<endl;

    thread first(fun1);
    thread second(fun2,666);

    first.join();
    second.join();

    cout<<__func__<<"-------------------------------"<<endl;
}

void fun1()
{
    cout<<__func__
       <<"[SubThread]:pid:"<<getpid()<<" tid:"<<this_thread::get_id()<<endl;
}

void fun2(const int num)
{
    cout<<__func__
       <<"[SubThread]:pid:"<<getpid()<<" tid:"<<this_thread::get_id()
      <<" Param:"<<num<<endl;
}

void SleepTest()
{
    cout<<__func__<<"-------------------------------"<<endl;

    for(int i=0;i<5;++i){
        cout<<i<<" ";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    cout<<endl;

    cout<<__func__<<"-------------------------------"<<endl;
}

void timeTest()
{
    cout<<__func__<<"-------------------------------"<<endl;

    auto start =std::chrono::system_clock::now();
    cout<<"fibonacii:"<<fibonacii(41)<<endl;
    auto end =std::chrono::system_clock::now();
    //计算时间差
    std::chrono::duration<double> elapsed_time=end-start;

    //获取当前时间
    std::time_t end_time=std::chrono::system_clock::to_time_t(end);

    cout<<"current time:"<<std::ctime(&end_time)
       <<"elapsed time:"<<elapsed_time.count()
      <<"s"<<endl;

    cout<<__func__<<"-------------------------------"<<endl;
}
long fibonacii(unsigned int n)
{
    if(n<2)return n;
    return fibonacii(n-1)+fibonacii(n-2);
}










































