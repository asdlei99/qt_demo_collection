#ifndef TIMER_H
#define TIMER_H

#include "lst_timer.h"

//定时器测试管理函数
void timer_test_manager();

//超时连接
/*设置超时时间，当超时时间结束，connect函数返回-1，连接失败，并置
errno=EINPROGRESS.可以对此情况进行特殊的操作*/
int timeout_connect(const char *ip,const int port,const int time);
void timeout_test();

//利用定时器处理非活动连接
/*服务器程序通常要定期处理非活动连接：给客户端发送一个重连请求，或者关闭该链接，或者其他。
在应用层实现模拟内核KEEPALIVE定期检查连接机制，一管理所有长时间处于非活动状态的连接。
本例利用alarm函数周期性地触发SIGLALRM信号，该信号的信号处理函数利用管道通知主循环执行
定时器链表上的定时任务--关闭非活动的连接。*/
void timer_test();
//函数主要作用，处理非活动的连接。
void timer_test_connect(const char *ip,const int port);
//设置连接描述为非阻塞
int timer_test_setnonblocking( int fd );
//添加连接文件描述符到事件中
void timer_test_addfd( int epollfd, int fd );
//信号处理函数
void timer_test_sig_handler( int sig );
//为指定的信号添加信号处理函数
void timer_test_addsig( int sig );
//定时器超时处理函数
void timer_test_timer_handler();
//删除epoll关键字上的文件描述符
void timer_test_cb_func( client_data* user_data );



#endif // TIMER_H
