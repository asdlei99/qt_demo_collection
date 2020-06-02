#include "epoll.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 1024

void epoll_fun(const char *ip, const unsigned int port)
{
    int ret = 0;
    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    //IPv4模式
    address.sin_family = AF_INET;
    //将点分十进制转化为二进制ip地址。
    inet_pton( AF_INET, ip, &address.sin_addr );
    //端口，将主机字节顺序转为网络字节顺序
    address.sin_port = htons( port );

    int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( listenfd >= 0 );
    //设置端口复用
    int opt=1;
    if(-1==setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR ,&opt,sizeof(int))){
        perror("setockopt SO_REUSEADDR failed.\n");
        return;
    }
    ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
    if(ret==-1){
        perror("Bind failed");
        return;
    }

    ret = listen( listenfd, 5 );
    if(ret==-1){
        perror("Listen failed");
        return;
    }

    epoll_event events[ MAX_EVENT_NUMBER ];
    /* int epoll_create(int size);
     * 返回一个内核事件表的文件描述符，来标识内核中的这个事件表，
     * 参数，给内核一个提示，表示事件表监听数目有多大。
     */
    int epollfd = epoll_create( 5 );
    assert( epollfd != -1 );
    //将需要被监听的文件描述符添加到opell描述符对应的事件结构体中。
    addfd( epollfd, listenfd, true );

    while( 1 )
    {
        /*int epoll_wait(int epfd,struct epoll_event   events,int maxevents,int timeout)
         * 在一段超时时间内等待一组文件描述符上的事件
         * 返回值是就绪文件描述符的个数，失败返回-1
         * 参数一，opell文件描述符。
         * 参数二，events用来从内核中得到事件集合，epoll_event类型的数组。
         * 参数三，指最多监听多少个事件，必须大于。第二个参数数组的个数。
         * 参数四，结构体，表示超时时间。
         */
        int ret = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1 );
        if ( ret < 0 )
        {
            printf( "epoll_wait failure\n" );
            break;
        }
        //Level Trigger,水平沿触发模式，只支持非阻塞socket
        lt( events, ret, epollfd, listenfd );
        //Edge Trigger,边沿触发模式,支持阻塞或非阻塞socket
        //et( events, ret, epollfd, listenfd );
    }

    close( listenfd );
}

//设置描述符非阻塞
int setnonblocking( int fd )
{
    /*修改已打开的文件描述符的性质。
     *  int fcntl(int fd, int cmd, ... /* arg / );
     * F_GETFL 获取文件描述符的状态。
     * F_SETFL 设置文件描述符的状态
     *
      */
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}
//将描述符添加到结构体中
void addfd( int epollfd, int fd, bool enable_et )
{
    /*
typedef union epoll_data {  联合体，
    void ptr;
    int fd;     //指定事件从属的文件描述符。
    __uint32_t u32;
    __uint64_t u64;
} epoll_data_t;

struct epoll_event {
    __uint32_t events;    / Epoll events /  epoll事件
    epoll_data_t data;    / User data variable /  用户数据
};
     */
    epoll_event event;
    event.data.fd = fd;
    //EPOLLIN表示数据可读事件
    event.events = EPOLLIN;
    if( enable_et )
    {
        /*EPOLLET 表示设置为Edge Trigger,边沿触发，默认为Level Trigger水平触发。
         * LT模式相当于一个高效的poll模式，ET模式是高效的epoll模式。
         * LT模式，当epoll检测到有事件发生并且通知应用程序后，应用程序可以
         * 不立即处理该事件。当应用程序下次调用epoll_wait函数时，还会再次通告
         * 此事件。
         */
        event.events |= EPOLLET;
    }
    /*将被监听的文件描述符添加到epoll描述符对应的事件结构体中。
     * int epoll_ctl(int epfd, int op, int fd, struct epoll_event event)
     * 参数一，epfd要操作的文件描述符。
     * 参数二，op指定的操作类型，
     * EPOLL_CTL_ADD,向事件表中注册参数一fd代表的文件描述符上的事件，
     * EPOLL_CTL_MOD,修改fd上的事件。
     * EPOLL_CTL_DEL,删除fd上的事件。
     * 参数三，fd关联的文件描述符。
     * 参数四，event，epoll_event 类型
     */
    epoll_ctl( epollfd, EPOLL_CTL_ADD, fd, &event );
    //设置描述符非阻塞
    setnonblocking( fd );
}
//Level Trigger,水平触发模式，（阻塞或者非阻塞）读取描述符中的数据
void lt( epoll_event* events, int number, int epollfd, int listenfd )
{
    char buf[ BUFFER_SIZE ];
    for ( int i = 0; i < number; i++ )
    {
        int sockfd = events[i].data.fd;
        int connfd=0;
        if ( sockfd == listenfd )
        {
            struct sockaddr_in client_address;
            socklen_t client_addrlength = sizeof( client_address );
            connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
            if(connfd==-1){
                perror("Accept failed");
                continue;
            }
            addfd( epollfd, connfd, false );
        }
        //EPOLLIN表示数据可读事件
        else if ( events[i].events & EPOLLIN )
        {
#if 1
            //获取客户端信息
            struct sockaddr_in client_addr;
            int len=sizeof(client_addr);
            memset(&client_addr,0,len);
            if(-1==getpeername(sockfd,(struct sockaddr*)&client_addr,
                               (socklen_t*)&len)){
                perror("Getsockname failed");
                //                                continue;
                //                return;
                exit(1);
            }

            //将点分十进制数字转化为字符串--网络地址
            //将网络字节序转化为主机字节序--端口
            //            printf("[Client info] %s:%d\n",inet_ntoa(client_addr.sin_addr),
            //                   ntohs(client_addr.sin_port));
#endif

            memset( buf, '\0', BUFFER_SIZE );
            int ret = recv( sockfd, buf, BUFFER_SIZE-1, 0 );
            if( ret <= 0 )
            {
                perror("Recv failed");
                //                close( sockfd );
                continue;
            }
            printf( "[Rev %s:%d]:%s\n",inet_ntoa(client_addr.sin_addr),
                    ntohs(client_addr.sin_port),buf );
            //            printf("[Rev]:%s\n",buf);
        }
        else
        {
            //            printf( "something else happened \n" );
            perror("something else happened");
        }
    }
}
//Edge Trigger边沿触发模式，读取数据
void et( epoll_event* events, int number, int epollfd, int listenfd )
{
    char buf[ BUFFER_SIZE ];
    for ( int i = 0; i < number; i++ )
    {
        int sockfd = events[i].data.fd;
        if ( sockfd == listenfd )
        {
            struct sockaddr_in client_address;
            socklen_t client_addrlength = sizeof( client_address );
            int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
            addfd( epollfd, connfd, true );
        }
        else if ( events[i].events & EPOLLIN )
        {
            printf( "event trigger once\n" );
            while( 1 )
            {
                memset( buf, '\0', BUFFER_SIZE );
                int ret = recv( sockfd, buf, BUFFER_SIZE-1, 0 );
                if( ret < 0 )
                {
                    if( ( errno == EAGAIN ) || ( errno == EWOULDBLOCK ) )
                    {
                        printf( "read later\n" );
                        break;
                    }
                    close( sockfd );
                    break;
                }
                else if( ret == 0 )
                {
                    close( sockfd );
                }
                else
                {
                    printf( "get %d bytes of content: %s\n", ret, buf );
                }
            }
        }
        else
        {
            printf( "something else happened \n" );
        }
    }
}

void epoll_test()
{
    printf("%s\n",__func__);
    const char *ip="0.0.0.0";
    int port=49153;

    epoll_fun(ip,port);
}
