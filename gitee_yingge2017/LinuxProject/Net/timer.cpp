#include "timer.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/epoll.h>

int timeout_connect(const char *ip, const int port, const int time)
{
    int ret = 0;
    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );

    int sockfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( sockfd >= 0 );

    struct timeval timeout;
    timeout.tv_sec = time;
    timeout.tv_usec = 0;
    socklen_t len = sizeof( timeout );
    //设置socket的超时时间timeout
    ret = setsockopt( sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len );
    assert( ret != -1 );
    //当超时时间内没有连接成功，返回值-1，且errno==EINPROGRESS
    ret = connect( sockfd, ( struct sockaddr* )&address, sizeof( address ) );
    if ( ret == -1 )
    {
        if( errno == EINPROGRESS )
        {
            //            printf( "connecting timeout\n" );
            perror("connecting timeout");
            return -1;
        }
        perror( "error occur when connecting to server" );
        return -1;
    }

    return sockfd;
}

void timeout_test()
{
    //    const char* ip = "192.168.11.1";
    const char *ip="127.0.0.1";
    const int port = 49152;

    int sockfd = timeout_connect( ip, port, 10 );
    if ( sockfd < 0 )
    {
        printf("%s:scokfd failed.\n",__func__);
        return;
    }
}

void timer_test_manager()
{
    printf("%s\n",__func__);
    //    timeout_test();
    timer_test();
}

//定时器测试函数
#define FD_LIMIT 65535//scoket描述符最大值？
#define MAX_EVENT_NUMBER 1024
#define TIMESLOT 5 //报警超时时间

static int pipefd[2];
static sort_timer_lst timer_lst;
static int epollfd = 0;

void timer_test()
{
    const char *ip="127.0.0.1";
    const int port = 49152;
    timer_test_connect(ip,port);
}

void timer_test_connect(const char *ip, const int port)
{
    int ret = 0;
    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );

    int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( listenfd >= 0 );

    ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
    assert( ret != -1 );

    ret = listen( listenfd, 5 );
    assert( ret != -1 );

    epoll_event events[ MAX_EVENT_NUMBER ];
    int epollfd = epoll_create( 5 );
    assert( epollfd != -1 );
    //添加连接文件描述符到事件中
    timer_test_addfd( epollfd, listenfd );
    /*　int socketpair(int domain, int type, int protocol, int sv[2]);
     * 套接字可以非网络进程间通信。
     */
    ret = socketpair( PF_UNIX, SOCK_STREAM, 0, pipefd );
    assert( ret != -1 );

    timer_test_setnonblocking( pipefd[1] );//设置操作符为非阻塞
    timer_test_addfd( epollfd, pipefd[0] );

    // add all the interesting signals here
    //为指定的信号添加信号处理函数
    timer_test_addsig( SIGALRM );
    timer_test_addsig( SIGTERM );

    client_data* users = new client_data[FD_LIMIT];
    bool timeout = false;
    //设置报警超时时间
    alarm( TIMESLOT );

    bool stop_server = false;
    while( !stop_server )
    {
        //int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout)
        //maxevents不能大于epoll_creat创建的数值。
        //函数返回可以读取数据的文件描述符。
        //最后一个参数是超时时间，-1表示阻塞。
        //The memory area pointed to by events will con‐
        //        tain  the  events  that  will be available for the caller.

        int number = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1 );
        //当错误号为EINTR，说明函数被更高级的终端打断了，应当忽略这个错误，认为正常，继续下面的操作。
        if ( ( number < 0 ) && ( errno != EINTR ) )
        {
            printf( "epoll failure\n" );
            break;
        }

        for ( int i = 0; i < number; i++ )
        {
            int sockfd = events[i].data.fd;
            //处理信道的客户连接
            if( sockfd == listenfd )
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof( client_address );
                //socket描述符的范围是多少？users数组能装的下吗？
                //client_data* users = new client_data[FD_LIMIT];
                //accept是阻塞还是非阻塞
                int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
                timer_test_addfd( epollfd, connfd );
                users[connfd].address = client_address;
                users[connfd].sockfd = connfd;
                //创建定时器
                util_timer* timer = new util_timer;
                timer->user_data = &users[connfd];
                timer->cb_func = timer_test_cb_func;//指定定时器处理函数
                time_t cur = time( NULL );//获取当前时间
                timer->expire = cur + 3 * TIMESLOT;//设置定时器超时时间
                users[connfd].timer = timer;
                //将定时器添加到定时器链表中
                timer_lst.add_timer( timer );
            }
            /* struct epoll_event {
               uint32_t     events;    /* Epoll events
               epoll_data_t data;      /* User data variable
           };*/
            // EPOLLIN：表示对应的文件描述符可以读。
            //处理信号
            //当socket是读端时
            else if( ( sockfd == pipefd[0] ) && ( events[i].events & EPOLLIN ) )
            {
                int sig;
                char signals[1024];
                ret = recv( pipefd[0], signals, sizeof( signals ), 0 );
                if( ret == -1 )
                {
                    // handle the error
                    perror("Recv failed");
                    continue;
                }
                else if( ret == 0 )
                {
                    continue;
                }
                else
                {
                    for( int i = 0; i < ret; ++i )
                    {
                        switch( signals[i] )
                        {
                        case SIGALRM:
                        {
                            timeout = true;
                            break;
                        }
                        case SIGTERM:
                        {
                            stop_server = true;
                        }
                        }
                    }
                }
            }
            //处理客户连接上收到的数据
            // EPOLLIN：表示对应的文件描述符可以读。
            else if(  events[i].events & EPOLLIN )
            {
                memset( users[sockfd].buf, '\0', BUFFER_SIZE );
                ret = recv( sockfd, users[sockfd].buf, BUFFER_SIZE-1, 0 );
                printf( "get %d bytes of client data %s from %d\n", ret, users[sockfd].buf, sockfd );
                util_timer* timer = users[sockfd].timer;
                if( ret < 0 )
                {
                    //EAGAIN：套接字已标记为非阻塞，而接收操作被阻塞或者接收超时
                    //                    对非阻塞socket而言，EAGAIN不是一种错误。
                    if( errno != EAGAIN )//有错误发生，从epoll上面删除该描述符
                    {
                        timer_test_cb_func( &users[sockfd] );//从epoll上面删除该描述符
                        if( timer )
                        {
                            timer_lst.del_timer( timer );//从定时器链表中删除该定时器。
                        }
                    }
                }
                //对方已经关闭连接（？），我们也关闭连接，删除 定时器。
                else if( ret == 0 )
                {
                    timer_test_cb_func( &users[sockfd] );
                    if( timer )
                    {
                        timer_lst.del_timer( timer );
                    }
                }
                else //ret >0 ,接收到数据，调整定时器，以延迟该连接的被关闭时间。
                {
                    printf("[Rev]:%s\n",users[sockfd].buf);
                    //send( sockfd, users[sockfd].buf, BUFFER_SIZE-1, 0 );
                    if( timer )
                    {
                        time_t cur = time( NULL );
                        timer->expire = cur + 3 * TIMESLOT;
                        printf( "adjust timer once\n" );
                        timer_lst.adjust_timer( timer );
                    }
                }
            }
            else
            {
                // others
            }
        }
        /*最后处理定时事件，因为IO事件有更高的优先级。
这样做会使定时任务不能按照预期时间执行。*/
        if( timeout )
        {
            timer_test_timer_handler();
            timeout = false;
        }
    }

    close( listenfd );
    close( pipefd[1] );
    close( pipefd[0] );
    delete [] users;
    return ;
}


//设置连接描述为非阻塞
int timer_test_setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}
//添加连接文件描述符到事件中
void timer_test_addfd( int epollfd, int fd )
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
    //EPOLLIN表示数据可读事件，EPOLLET设置为LT模式。
    event.events = EPOLLIN | EPOLLET;
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
    timer_test_setnonblocking( fd );
}
//信号处理函数
void timer_test_sig_handler( int sig )
{
    int save_errno = errno;
    int msg = sig;
    send( pipefd[1], ( char* )&msg, 1, 0 );
    errno = save_errno;
}
//为指定的信号添加信号处理函数
void timer_test_addsig( int sig )
{
    struct sigaction sa;
    memset( &sa, '\0', sizeof( sa ) );
    sa.sa_handler = timer_test_sig_handler;
    //SA_RESTART 设置该标识，在信号触发信号函数时，能够保存当前系统函数的状态，
    //并在信号处理函数结束后，恢复原先的系统函数。
    sa.sa_flags |= SA_RESTART;
    //将所有信号加入到此信号集中，在信号处理函数执行过程中，阻塞所有其他信号。
    sigfillset( &sa.sa_mask );
    assert( sigaction( sig, &sa, NULL ) != -1 );
}
//定时器超时处理函数
void timer_test_timer_handler()
{
    timer_lst.tick();
    alarm( TIMESLOT );
}
//删除epoll关键字上的文件描述符
void timer_test_cb_func( client_data* user_data )
{
    //从epoll关键字上删除某文件描述符
    epoll_ctl( epollfd, EPOLL_CTL_DEL, user_data->sockfd, 0 );
    assert( user_data );
    //关闭sock文件描述符
    close( user_data->sockfd );
    printf( "close fd %d\n", user_data->sockfd );
}
