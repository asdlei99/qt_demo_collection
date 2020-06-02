#include "process_test.h"
#include "fifo_test.h"
#include <stdio.h>
#include "fork_test.h"
#include "pipe_test.h"
#include "messagequeue.h"
#include "sharedmemory.h"

void process_test()
{
    printf("%s\n",__func__);

//    fork_test_manager();	//多进程

//    pipe_test_manager();	//管道
    fifo_test_manager();	//有名管道
//    messagequeue_test();	//消息队列
//    sharedmemory_test();	//共享内存

//信号量
//信号
//套接字
} 
