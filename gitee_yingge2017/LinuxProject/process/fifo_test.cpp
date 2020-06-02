#include "fifo_test.h"
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "sys/stat.h"
#include "sys/types.h"
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>

#if 1
void fifo_test_manager()
{
    //    fifo_test_server();
    fifo_test_simple();
}

void fifo_test_server()
{
    int serverFd, dummyFd, clientFd;
    char clientFifo[CLIENT_FIFO_NAME_LEN];
    struct request req; //请求
    struct response resp; //回答
    int seqNum = 0;                     /* This is our "service" */

    /* Create well-known FIFO, and open it for reading */

    /* mode_t umask(mode_t mask);
     * 设置新建文件的权限遮罩。
     *  umask()会将系统umask值设成参数mask&0777后的值，然后将先前的umask值返回。
     * 在使用open()建立新文件时，该参数 mode并非真正建立文件的权限，而是(mode& ~umask)的权限值。
     * 例如，在建立文件时指定文件权限为0666，通常umask值默认为 022，
     * 则该文件的真正权限则为0666&～022＝0644，也就是rw-r--r--返回值此调用不会有错误值返回。
     */
    umask(0); //不屏蔽任何权限

    if (mkfifo(SERVER_FIFO, S_IRUSR | S_IWUSR | S_IWGRP) == -1
        && errno != EEXIST){
        //        errExit("mkfifo %s", SERVER_FIFO);
        perror("mkfifo failed");
        return;
    }
    //打开服务器FIFO
    serverFd = open(SERVER_FIFO, O_RDONLY);
    if (serverFd == -1){
        //        errExit("open %s", SERVER_FIFO);
        perror("open failed");
        return;
    }

    /* Open an extra write descriptor, so that we never see EOF */
    //第二个打开操作，是为了服务器在所有的客户端关闭了FIFO的写入端后，不会看到文件的结束。
    dummyFd = open(SERVER_FIFO, O_WRONLY);
    if (dummyFd == -1){
        //        errExit("open %s", SERVER_FIFO);
        perror("open failed");
        return;
    }

    /* Let's find out about broken client pipe via failed write() */
    //忽略SIGPIPE信号，如果服务器向一个没有读者的FIFO写入数据时，
    //不会收到SIGPIPE信号，该信号默认会杀死进程，而是会从write收到一个
    //EPIPE错误
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR){
        //        errExit("signal");
        perror("signal failed");
        return;
    }

    for (;;) {                          /* Read requests and send responses */
        if (read(serverFd, &req, sizeof(struct request))
            != sizeof(struct request)) {
            fprintf(stderr, "Error reading request; discarding\n");
            continue;                   /* Either partial read or error */
        }

        /* Open client FIFO (previously created by client) */
        //向管道中写入数据。
        snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE,
                 (long) req.pid);
        //打开客户端已经打开的FIFO，如果打开失败就丢弃这个请求。
        clientFd = open(clientFifo, O_WRONLY);
        if (clientFd == -1) {           /* Open failed, give up on client */
            //            errMsg("open %s", clientFifo);
            perror("open failed");
            continue;
        }

        /* Send response and close FIFO */
        resp.seqNum = seqNum;
        if (write(clientFd, &resp, sizeof(struct response))
            != sizeof(struct response))
            fprintf(stderr, "Error writing to FIFO %s\n", clientFifo);
        if (close(clientFd) == -1){
            //            errMsg("close");
            perror("close failed");
            return;
        }

        seqNum += req.seqLen;           /* Update our sequence number */
    }//end for
}

#endif

#if 0
void fifo_test_client()
{
    int serverFd, clientFd;
    struct request req;
    struct response resp;

    //    if (argc > 1 && strcmp(argv[1], "--help") == 0)
    //        usageErr("%s [seq-len]\n", argv[0]);

    /* Create our FIFO (before sending request, to avoid a race) */

    umask(0);                   /* So we get the permissions we want */
    snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE,
             (long) getpid());
    if (mkfifo(clientFifo, S_IRUSR | S_IWUSR | S_IWGRP) == -1
        && errno != EEXIST){
        perror("mkfifo failed");
        return;
    }

    //    注册终止函数(即main执行结束后调用的函数)
    //    void atexit(void (*func)(void));
    if (atexit(removeFifo) != 0)
        errExit("atexit");

    /* Construct request message, open server FIFO, and send message */

    req.pid = getpid();
    //    req.seqLen = (argc > 1) ? getInt(argv[1], GN_GT_0, "seq-len") : 1;

    serverFd = open(SERVER_FIFO, O_WRONLY);
    if (serverFd == -1){
        perror("open server fifo failed");
        return;
    }

    if (write(serverFd, &req, sizeof(struct request)) !=
        sizeof(struct request)){
        perror("write failed");
        return;
    }
    //        fatal("Can't write to server");

    /* Open our FIFO, read and display response */

    clientFd = open(clientFifo, O_RDONLY);
    if (clientFd == -1){
        perror("open clientFifo failed");
        return;
    }
    //        errExit("open %s", clientFifo);

    if (read(clientFd, &resp, sizeof(struct response))
        != sizeof(struct response)){
        perror("read clientFd failed");
        return;
    }
    //    fatal("Can't read response from server");

    printf("%d\n", resp.seqNum);
    //    exit(EXIT_SUCCESS);
    exit(0);
}
#endif

void fifo_test_simple()
{
    const char *filePath="/mnt/fifo_test_file";

    if(fopen(filePath,"r")!=NULL){
        unlink(filePath);
        if(remove(filePath)==-1){
            perror("remove failed");
            return;
        }
    }

    if (mkfifo(filePath, S_IRUSR | S_IWUSR | S_IWGRP) == -1){
        perror("mkfifo failed");
        return;
    }

    pid_t pid=fork();
    if(pid==-1){
        perror("fork failed");
        return;
    }
    else if(pid==0){//child
        int fd=open(filePath,O_RDONLY);
        if(fd==-1){
            perror("open failed");
            return;
        }

        char buf[100]={0};
        //        memcpy(buf,"0",100);
        memset(buf,0,100);
        int count=0;
        while(1){
            sleep(1);
            if(count==3)
                exit(0);
            else
                ++count;

            int re=read(fd,buf,100);
            if(re==-1){
                perror("read failed");
                exit;
            }
            else{
                buf[re]='\0';
                printf("Child:%s\n",buf);
//                fflush(1);
                //                memcpy(buf,'0',100);
                memset(buf,0,100);
            }

        }
    }
    //parent
    int fd=open(filePath,O_WRONLY);
    if(fd==-1){
        perror("open failed");
        return;
    }

    char buf[100]={0};
    int count=100;
    while(1){
        sleep(1);
        if(count==3)
            exit(0);
        else
            ++count;

        memcpy(buf,"Num:",strlen("Num:"));
        sprintf(buf,"%d",count);
        //        write(fd,&count,sizeof(count));
        write(fd,&buf,100);
        memset(buf,0,100);
    }
    wait(NULL);
}
