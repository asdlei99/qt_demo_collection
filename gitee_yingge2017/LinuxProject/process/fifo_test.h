#ifndef FIFO_TEST_H
#define FIFO_TEST_H

#include <unistd.h>

#define SERVER_FIFO "/tmp/seqnum_sv"
                                /* Well-known name for server's FIFO */
#define CLIENT_FIFO_TEMPLATE "/tmp/seqnum_cl.%ld"
                                /* Template for building client FIFO name */
#define CLIENT_FIFO_NAME_LEN (sizeof(CLIENT_FIFO_TEMPLATE) + 20)
                                /* Space required for client FIFO pathname
                                  (+20 as a generous allowance for the PID) */
//请求
struct request {                /* Request (client --> server) */
    pid_t pid;                  /* PID of client */
    int seqLen;                 /* Length of desired sequence */
};
//回答
struct response {               /* Response (server --> client) */
    int seqNum;                 /* Start of sequence */
};


void fifo_test_manager();
void fifo_test_client();
void fifo_test_server();

static char clientFifo[CLIENT_FIFO_NAME_LEN];
//头文件：#include <unistd.h>
//定义函数：int unlink(const char * pathname);
//函数说明：unlink()会删除参数pathname 指定的文件. 如果该文件名为最后连接点,
//但有其他进程打开了此文件, 则在所有关于此文件的文件描述词皆关闭后才会删除. 如果参数pathname 为一符号连接, 则此连接会被删除。
static void             /* Invoked on exit to delete client FIFO */
removeFifo(void)
{
    unlink(clientFifo);
}

void fifo_test_simple();

#endif // FIFO_TEST_H
