#include "client.h"
#include <vector>
#include  <thread>
#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

#define BUFFER_SIZE 512

//const char *ip="192.168.1.108";
//const int port=49152;

void clientConnect(const char *ip, const unsigned int port){
    if(ip==NULL)
    {
        printf("ip is NULL.\n");
        return ;
    }
    struct sockaddr_in server_address;
    //类型内容置空
    bzero( &server_address, sizeof( server_address ) );
    //IPv4网络协议
    server_address.sin_family = AF_INET;
    //ip地址点分十进制转换为二进制
    inet_pton( AF_INET, ip, &server_address.sin_addr );
    //主机字节序转为网络字节序
    server_address.sin_port = htons( port );
    //稳定数据传输，tcp协议
    int sock = socket( AF_INET, SOCK_STREAM, 0 );
    if(sock==-1){
        perror("socket failed:");
        return;
    }
    //int sendbuf = atoi( argv[3] );
    int sendbuf = 32*1024;
    int len = sizeof( sendbuf );
    //设置套接字选项
    setsockopt( sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, sizeof( sendbuf ) );
    getsockopt( sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, ( socklen_t* )&len );

    printf( "the tcp send buffer size after setting is %d\n", sendbuf );

    while (-1 ==connect( sock, ( struct sockaddr* )&server_address,
                         sizeof( server_address ) ) ){
        perror("connect:");
        printf("Reconnect.\n");
        //        fflush(stdout);
        sleep(1);
        //        return ;
    }
    while(true)
    {
#if 0
        char buffer[ BUFFER_SIZE ];
        //用字符充满内存
        memset( buffer, 'a', BUFFER_SIZE );
        int num=send( sock, buffer, BUFFER_SIZE, 0 );
#endif
        const char *buffer="this is client.";
        int num=send( sock, buffer, strlen(buffer), 0 );
        printf("Send num:%d,threadid:%lu.\n",num,this_thread::get_id());

        sleep(1);
    }

    close( sock );

    printf("socket close.\n");
    fflush(stdout);
}

void clientTest()
{
    const char *ip="192.168.1.108";
    int port=49153;
    clientConnect(ip,port);
}

void threadClient()
{
    vector<thread> thdVtr;
    for(int i=0;i<10;++i){
        thread new_thread(clientTest);
        //        thread new_thread(fun);
        //使用stl:move,将不使用拷贝构造函数， 避免不必要的拷贝操作。
        thdVtr.push_back(move(new_thread));
        //        thdVtr.push_back(new_thread);

        printf("new thread create.\n");
    }

    //遍历器获取到的是指针类型
    vector<thread>::iterator it=thdVtr.begin();
    for(;it<thdVtr.end();++it){
        (*it).join();
    }
    //        for (auto &iter : thdVtr) {
    //            (*iter).join();
    //        }
#if 0
    //错误，使用thread的拷贝构造函数。
    //    for(int i=0;i<thdVtr.size();++i){
    //        thread t=static_cast<thread>(thdVtr[i]);
    //        t.join();
    //    }
#endif
}

void fun()
{
    printf("thread id:%d.\n",this_thread::get_id());
}



