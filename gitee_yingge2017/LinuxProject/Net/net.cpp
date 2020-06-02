#include "net.h"
#include "stdio.h"
#include "server.h"
#include "timer.h"
#include "epoll.h"
#include "libevent_test.h"


void NetTest(){
    printf("%s\n",__func__);

    //    byteorder();
    //    clientTest();
    //多线程客户端测试函数
    //    threadClient();
    //服务器测试函数
    //    serverTest();
    //
    //    epoll_test();
    //    timer_test_manager();
//    libevent_test_manager();
}

void byteorder()
{
#if 1
    union
    {
        short value;
        char union_bytes[ sizeof( short ) ];
    } test;
    test.value = 0x0102;
    if (  ( test.union_bytes[ 0 ] == 1 ) && ( test.union_bytes[ 1 ] == 2 ) )
    {
        printf( "big endian\n" );
    }
    else if ( ( test.union_bytes[ 0 ] == 2 ) && ( test.union_bytes[ 1 ] == 1 ) )
    {
        printf( "little endian\n" );
    }
    else
    {
        printf( "unknown...\n" );
    }
#endif
#if 0
    union {
        int data;
        char bytes[4];
    }test;

    test.data=0x01020304;
    if(test.bytes[0]==1 && test.bytes[1]==2)
    {
        printf("big\n");
    }
    else if(test.bytes[0]==4 && test.bytes[1]==3){
        printf("little\n");
    }
#endif
}
