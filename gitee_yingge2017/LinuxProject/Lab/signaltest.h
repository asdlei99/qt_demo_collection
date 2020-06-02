#ifndef SIGNALTEST_H
#define SIGNALTEST_H

#include <signal.h>

//测试总函数
void signal_test_manager();

//阻塞信号
void signal_test1();
//
void signal_test2();
void signal_myhandler(const int);
void signal_myset(struct sigaction*act);

//演示sigqueue在发送信号的同时发送数据
void signal_test3();
void signal_test3_handler(int signo,siginfo_t *si,void *ucontext);

//在另一个shell发送信号:kill -44 4579
void signal_test4();
void signal_test4_handler(int signo,siginfo_t *si,void *ucontext);

//多进程间信号例子1(暂时有问题)
void signal_test5();
void signal_test5_changevalue(int);
void signal_test5_stop(int);

#endif
































