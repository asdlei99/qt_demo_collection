#include "server.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

const int BUFFER_SIZE=1024;

void server(const char *ip, const unsigned int port)
{
    //    if( argc <= 3 )
    //    {
    //        printf( "usage: %s ip_address port_number receive_buffer_size\n", basename( argv[0] ) );
    //        return 1;
    //    }
    //    const char* ip = argv[1];
    //    int port = atoi( argv[2] );

    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );

    int sock = socket( PF_INET, SOCK_STREAM, 0 );
    if(sock==-1){
        perror("socket failed.");
        return;
    }
#if 0
    int recvbuf = atoi( argv[3] );
    int len = sizeof( recvbuf );
    setsockopt( sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, sizeof( recvbuf ) );
    getsockopt( sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, ( socklen_t* )&len );
    printf( "the receive buffer size after settting is %d\n", recvbuf );
#endif
    int opt=1;
    if(-1==setsockopt(sock,SOL_SOCKET,SO_REUSEADDR ,&opt,sizeof(int))){
        perror("setockopt SO_REUSEADDR failed.\n");
        return;
    }
    int ret = bind( sock, ( struct sockaddr* )&address, sizeof( address ) );
    if(ret==-1){
        perror("bind failed.");
        return;
    }
    ret = listen( sock, 5 );
    if(ret==-1){
        perror("listen failed.");
        return;
    }

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof( client );
    printf("[Listen]%s:%d\n",ip,port);
    int connfd = accept( sock, ( struct sockaddr* )&client, &client_addrlength );
    if ( connfd==-1)
    {
        //        printf( "errno is: %d\n", errno );
        perror("connect failed.");
        return;
    }
    else
    {
        struct sockaddr_in client_addr,server_addr;
        int len=sizeof(client_addr);
        //获取服务器信息
        memset(&server_addr,0,len);
        if(-1==getsockname(sock,(struct sockaddr*)&server_addr,
                           (socklen_t*)&len)){
            perror("getpeername failed.");
            return;
        }
        printf("[Listen info] %s:%d\n",inet_ntoa(server_addr.sin_addr),
               ntohs(server_addr.sin_port));

        //获取客户端信息
        memset(&client_addr,0,len);
        if(-1==getpeername(connfd,(struct sockaddr*)&client_addr,
                           (socklen_t*)&len)){
            perror("getsockname failed.");
        }
        printf("[Client info] %s:%d\n",inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port));
        //循环读取客户端发来数据
        char buffer[ BUFFER_SIZE ];
        memset( buffer, '\0', BUFFER_SIZE );
        while( recv( connfd, buffer, BUFFER_SIZE-1, 0 ) > 0 ){
            printf("[Server Rev][%s:%d]:%s\n",inet_ntoa(client_addr.sin_addr),
                   ntohs(client_addr.sin_port),buffer);
        }

        perror("Rev stop");
        close( connfd );
        return ;
    }

    perror("Close sock");
    close( sock );
    printf("socket close.\n");
}

void serverTest()
{
    printf("%s\n",__func__);
    const char *ip="0.0.0.0";
    int port=49153;
    //    server(ip,port);
    select_test(ip,port);
}

void select_test(const char *ip, const unsigned int port)
{
    printf( "ip is %s and port is %d\n", ip, port );

    int ret = 0;
    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );

    int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( listenfd >= 0 );

    int opt=1;
    if(-1==setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR ,&opt,sizeof(int))){
        perror("setockopt SO_REUSEADDR failed.\n");
        return;
    }
    ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
    assert( ret != -1 );

    ret = listen( listenfd, 5 );
    assert( ret != -1 );

    struct sockaddr_in client_address;
    socklen_t client_addrlength = sizeof( client_address );
    int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
    if ( connfd < 0 )
    {
        printf( "errno is: %d\n", errno );
        close( listenfd );
    }

    char remote_addr[INET_ADDRSTRLEN];
    printf( "connected with ip: %s and port: %d\n",
            inet_ntop( AF_INET, &client_address.sin_addr, remote_addr, INET_ADDRSTRLEN ),
            ntohs( client_address.sin_port ) );

    char buf[1024];
    fd_set read_fds;
    fd_set exception_fds;

    FD_ZERO( &read_fds );
    FD_ZERO( &exception_fds );
    //设置带外数据到普通数据
    int nReuseAddr = 1;
    setsockopt( connfd, SOL_SOCKET, SO_OOBINLINE, &nReuseAddr, sizeof( nReuseAddr ) );
    while( 1 )
    {
        memset( buf, '\0', sizeof( buf ) );
        FD_SET( connfd, &read_fds );
        FD_SET( connfd, &exception_fds );

        ret = select( connfd + 1, &read_fds, NULL, &exception_fds, NULL );
        printf( "select one\n" );
        if ( ret < 0 )
        {
            printf( "selection failure\n" );
            break;
        }

        if ( FD_ISSET( connfd, &read_fds ) )
        {
            ret = recv( connfd, buf, sizeof( buf )-1, 0 );
            if( ret <= 0 )
            {
                break;
            }
            printf( "get %d bytes of normal data: %s\n", ret, buf );
        }
        else if( FD_ISSET( connfd, &exception_fds ) )
        {
            ret = recv( connfd, buf, sizeof( buf )-1, MSG_OOB );
            if( ret <= 0 )
            {
                break;
            }
            printf( "get %d bytes of oob data: %s\n", ret, buf );
        }

    }

    perror("Close");

    close( connfd );
    close( listenfd );
}

