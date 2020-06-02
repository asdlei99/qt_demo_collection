#include "messagequeue.h"
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>

void my_perror(const char *funstr,const char *str)
{
    char buff[100]={0};
    sprintf(buff,"%s-%s",funstr,str);
    perror(buff);
}

#define MyPerror(str)  my_perror(__func__,str);

const char *file="/posix2";

const int BufferSize=8192;//msg大小

struct MsgType{
    int len;
    char buf[BufferSize];
    char x;
    short y;
};

void messagequeue_test()
{
    pid_t pid=fork();
    if(pid==-1){
        MyPerror("fork");
        return;
    }
    if(pid==0)//子进程
        mq_producer();
    //父进程
    sleep(1);
    mq_customer();
    wait(NULL);
    return;
}

//消费者
void mq_customer()
{
    mqd_t msgq_id;
    unsigned int sender;
    struct mq_attr msgq_attr;
    MsgType msg_data;

    msgq_id=mq_open(file,O_RDONLY);
    if(msgq_id==-1){
        MyPerror("mq_open");
        exit(1);
    }

    if(mq_getattr(msgq_id,&msgq_attr)==-1){
        MyPerror("mq_getattr");
        exit(1);
    }

    printf("\t mq_flag-mq_flags:%ld\n\t \
           队列中包含的消息数的最大限制数  mq_maxmsg:%ld\n\t \
           每个消息大小的最大限制数 mq_msgsize:%ld\n\t \
           当前队列中的消息数  mq_curmsg:%ld\n ",
           msgq_attr.mq_flags,
           msgq_attr.mq_maxmsg,
           msgq_attr.mq_msgsize,
           msgq_attr.mq_curmsgs
           );

    int i=0;
    char buff[8192]={0};
    while(i<10){
        msg_data.len=i;
        if(mq_receive(msgq_id,(char*)&msg_data,BufferSize,&sender)==-1){
            MyPerror("mq_receive");
            exit(1);
        }
        //        printf("Rev-data:%d\n",data);
        printf("%s-rev:%d\n",__FUNCTION__,msg_data.len);
        ++i;
        sleep(2);
    }
    if(mq_close(msgq_id)==-1){
        MyPerror("mq_close");
        exit(1);
    }

    return ;
}
//生产者
void mq_producer()
{
    mqd_t msgq_id;

    unsigned int prio=1;
    unsigned int send_size=-1;

    struct mq_attr msgq_attr;
    MsgType msg_data;

    //在生产者打开file之前保证已经关闭
    if(mq_unlink(file)==-1){
        MyPerror("mq_unlink");
//        exit(1);
    }

    msgq_id=mq_open(file,O_RDWR|O_CREAT,S_IRWXU|S_IRWXG,NULL);
    if(msgq_id==-1){
        MyPerror("mq_open");
        exit(1);
    }

    if(mq_getattr(msgq_id,&msgq_attr)==-1){
        MyPerror("mq_getattr");
        exit(1);
    }

    printf("\t mq_flag- mq_flags:%ld\n\t \
           队列中包含的消息数的最大限制数  mq_maxmsg:%ld\n\t \
           每个消息大小的最大限制数 mq_msgsize:%ld\n\t \
           当前队列中的消息数  mq_curmsg:%ld\n ",
           msgq_attr.mq_flags,
           msgq_attr.mq_maxmsg,
           msgq_attr.mq_msgsize,
           msgq_attr.mq_curmsgs
           );

    //    if(mq_setattr(msgq_id,&msgq_attr,NULL)==-1){
    //        MyPerror("mq_setattr");
    //        exit(1);
    //    }

    for(int i=0;i<10;++i){
        msg_data.len=i;
        printf("%s_send:%d\n",__FUNCTION__,msg_data.len);

        //        int mq_send(mqd_t mqdes, const char *msg_ptr,
        //                             size_t msg_len, unsigned msg_prio);
        if(mq_send(msgq_id,(char*)&msg_data,BufferSize,prio)==-1){
            MyPerror("mq_send");
            exit(1);
        }
        sleep(1);

    }

    sleep(3);//等待消费者进程退出

    if(mq_close(msgq_id)==-1){
        MyPerror("mq_close");
        exit(1);
    }

    if(mq_unlink(file)==-1){
        MyPerror("mq_unlink");
        exit(1);
    }

    return ;
}


