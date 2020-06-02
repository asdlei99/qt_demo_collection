#ifndef EPOLL_H
#define EPOLL_H

#include "sys/epoll.h"

/*epoll IO复用*/

//Edge Trigger边沿触发模式，读取数据
void et( epoll_event* events, int number, int epollfd, int listenfd );
//Level Trigger,水平触发模式，（阻塞或者非阻塞）读取描述符中的数据
void lt( epoll_event* events, int number, int epollfd, int listenfd );
//将描述符添加到结构体中
void addfd( int epollfd, int fd, bool enable_et );
//设置描述符非阻塞
int setnonblocking( int fd );
//
void epoll_fun(const char *ip, const unsigned int port);


//epoll测试函数
void epoll_test();


#endif // EPOLL_H
