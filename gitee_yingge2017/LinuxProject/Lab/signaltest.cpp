#include "signaltest.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void signal_test4()
{
    struct sigaction oldact,act;
    sigset_t oldmask,newmask,pendingmask;
    act.sa_sigaction=signal_test4_handler;
    act.sa_flags=SA_SIGINFO;//设置之后，表示可以使用传递信息的函数指针。
    sigemptyset(&act.sa_mask);//首先将阻塞集合设置为空，即不阻塞任何信号
    //注册信号处理函数
    sigaction(SIGRTMIN+10,&act,&oldact);
    //开始阻塞
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGRTMIN+10);
    printf("SIGRTMIN+10 blocked,\n");
    sigprocmask(SIG_BLOCK,&newmask,&oldmask);

    //等待接收信号
    while(true){
        static int count=0;
        if(count==20)
            break;
        else
            ++count;

        printf("waiting...%d \n",count);
        sleep(2);//为了发出信号
    }

    printf("now begin to get pending mask\n");
    //获得挂起信号集
    if(sigpending(&pendingmask)<0){
        perror("pendingmask error");
    }
    //判断信号集中有没有某信号
    if(sigismember(&pendingmask,SIGRTMIN+10)){
        printf("SIGRTMIN+10 is in the pending mask\n");
    }
    //删除挂起信号
    sigprocmask(SIG_UNBLOCK,&newmask,&oldmask);

    printf("SIGRTMIN+10 unblocked\n");
    exit(0);
}

void signal_test4_handler(int signo, siginfo_t *si, void *ucontext)
{
    printf("receive signal %d ---------------- \n",si->si_signo);
}

void signal_test_manager()
{
    //    signal_test1();
    //    signal_test2();
    //    signal_test3();
    signal_test4();
}

void signal_test1()
{
    sigset_t initset;
    int i;
    //初始化信号集合为空集合
    sigemptyset(&initset);
    //将SIGINT信号加入到此集合中去
    /*     int sigaddset(sigset_t *set,int signum);
     * 参数一是信号集结构体，参数二是需要添加的信号。
     */
    sigaddset(&initset,SIGINT);

    while(1)     {
        /*用于改变当前进程的阻塞信号集。
         * int sigprocmask(int how, const sigset_t *restrict newset, sigset_t *restrict oldset);
         * SIG_BLOCK,表示将newset所包含的信号添加到当前进程的信号屏蔽集中。
         * SIG_UNBLOCK,将newset所表示的信号从当前进程的信号屏蔽集中删除。
         * SIG_SETMASK，设置当前进程的信号屏蔽字为newset所表示的信号屏蔽集。
         */
        sigprocmask(SIG_BLOCK,&initset,NULL);
        printf("SIGINT singal blocked\n");
        for(i=0;i<10;i++){
            sleep(1);//每1秒输出
            printf("阻塞block SIGINT %d\n",i);
        }
        //在这时按一下Ctrl+C不会终止
        sigprocmask(SIG_UNBLOCK,&initset,NULL);//从进程的阻塞集合中去删除信号集合
        printf("SIGINT SINGAL unblokced\n");
        for(i=0;i<10;i++){
            sleep(1);
            printf("unblock %d\n",i);
        }

    }
}

void signal_test2()
{
    int i=0;
    struct sigaction act,oldact;
    act.sa_handler=signal_myhandler;
    //SA_RESETHAND在处理完信号后，将信号恢复成默认处理
    //SA_NODEFER在信号处理程序执行期间仍然可以接收信号
    //如果不加SA_NODEFER,程序会在执行函数中死循环。
    act.sa_flags=SA_RESETHAND | SA_NODEFER;
    /*        int sigaction(int signum, const struct sigaction *act,
    *                           struct sigaction *oldact);
    * 用来查询或设置信号的处理方式。
    * 参数一，signum指定需要查询或设置的信号，SIGKILL/SIGSTOP以外的所有信号。
    * 参数二，*act指定将要指定信号的行为
    * 参数三，*oldact指定之前信号的行为。
    */
    if(-1==sigaction(SIGINT,&act,&oldact)){
        perror("sigaction failed");
        return;
    }

    for(int i=0;i<12;++i){
        printf("signal %d handler is :",i);
        sigaction(i,NULL,&oldact);
        signal_myset(&oldact);
    }
    while(1){
        //等待信号到来
    }
}

void signal_myhandler(const int)
{
    static int count=0;
    printf(" 000xxxxx %d\n",count++);

    while(1){

    }
}

void signal_myset(struct sigaction *act)
{
    switch (act->sa_flags) {
    //SIG_DFL默认处理
    //    case (int)SIG_DFL:
    case 0:
        printf("using default handler.\n");
        break;
        //SIG_IGN忽略
        //    case (int)SIG_IGN:
    case 1:
        printf("ignore the signal.\n");
        break;
    default:
        printf("%0x \n",act->sa_handler);
        break;
    }
}
/*struct sigaction {
void (*sa_handler)(int);
void (*sa_sigaction)(int,siginfo_t*,void*);
sigset_t sa_mask;
int sa_flags;
void (*sa_restorer)(void);
}
结构体内容：
参数1： sa_handler是一个函数指针，主要表示接收到信号时所需要采取的行动，
此字段的值可以是SIG_DFL,SIG_IGN.分别代表默认操作与内核将忽略进程的信号。这个函数只传递一个参数那就是信号代码。
参数2 ：当SA_SIGINFO被设定在sa_flags中，那么则会使用sa_sigaction来指示信号处理函数，而非sa_handler.
参数3：sa_mask设置了掩码集，在程序执行期间会阻挡掩码集中的信号。
参数4：sa_flags设置了一些标志。例如， SA_RESETHAND当该函数处理完成之后，设定为为系统默认的处理模式。
SA_NODEFER 在处理函数中，如果再次到达此信号时，将不会阻塞。默认情况下，同一信号两次到达时，
如果此时处于信号处理程序中，那么此信号将会阻塞。SA_SIGINFO表示用sa_sigaction指示的函数。
参数5：sa_restorer已经废弃。

sa_sigaction所指向的函数原型:
void my_handler(int signo,siginfo_t *si,void *ucontext);
第一个参数: 信号编号
第二个参数:指向一个siginfo_t结构。
第三个参数:是一个ucontext_t结构。
其中siginfo_t结构体中包含了大量的信号携带信息，可以看出，这个函数比sa_handler要强大，
因为前者只能传递一个信号代码，而后者可以传递siginfo_t信息。
typedef struct siginfo_t{
int si_signo;//信号编号
int si_errno;//如果为非零值则错误代码与之关联
int si_code;//说明进程如何接收信号以及从何处收到
pid_t si_pid;//适用于SIGCHLD，代表被终止进程的PID
pid_t si_uid;//适用于SIGCHLD,代表被终止进程所拥有进程的UID
int si_status;//适用于SIGCHLD，代表被终止进程的状态
clock_t si_utime;//适用于SIGCHLD，代表被终止进程所消耗的用户时间
clock_t si_stime;//适用于SIGCHLD，代表被终止进程所消耗系统的时间
sigval_t si_value;//sigqueue函数发送过来的数据，也就是下面两个参数。
int si_int; //sigval结构中的sival_int
void * si_ptr;//sigval结构中的sival_ptr
void* si_addr;   /* Memory location which caused fault
int si_band; /* Band event
int si_fd; /* File descriptor
};
*/
void signal_test3_handler(int signo, siginfo_t *si, void *ucontext)
{
    printf("已经收到SIGUSR1信号.\n");
    //两种方式都能获得sigqueue函数发送过来的数据。
    printf("%s,%s\n",(char*)(si->si_ptr),(char*)(si->si_value.sival_ptr));
}
void signal_test3()
{
    union sigval val;
    struct sigaction act,oldact;
    act.sa_sigaction=signal_test3_handler;
    //SA_SIGINFO表示使用sa_sigaction指定的函数，处理完恢复默认，
    //不阻塞处理过程中到达下在被处理的信号。
    /* SA_SIGINFO (since Linux 2.2)
                  The  signal  handler  takes three arguments, not one.  In this case,
                  sa_sigaction should be set instead  of  sa_handler.   This  flag  is
                  meaningful only when establishing a signal handler.
     */
    act.sa_flags=SA_SIGINFO;

    sigaction(SIGUSR1,&act,&oldact);
    char data[100];
    int num=0;
    while(num<10){
        sleep(2);
        printf("等待SIGUSER1信号到来.\n");
        sprintf(data,"%d",num++);
        val.sival_ptr=data;

        //向本进程发送一个信号
        /*在队列中向指定进程发送一个信号和数据。
         * int sigqueue(pid_t pid,int sig,const union sigval value);
         * pid是进程号。
         * sig是信号代号。
         * value是union sigval联合体
         *  union sigval {
               int   sival_int;
               void *sival_ptr;
           };
           表示信号附带数据，附带数据可以使一个整数，也可以是一个指针。
         */
        sigqueue(getpid(),SIGUSR1,val);
    }

}

volatile int wait_flag=0;
void signal_test5()
{
    int pid1,pid2;
    //    signal(2,stop_info);
    signal(SIGINT,signal_test5_stop);

    wait_flag = 1;

    printf("before fork child1\n");
    while((pid1=fork())<0);
    printf("after fork child1\n");

    if(pid1>0)  //父进程
    {
        while((pid2=fork())<0);

        if(pid2>0)  //父进程
        {
            printf("parent id is %d\n",getpid());

//            int istatus=0;
//            wait(&istatus);
//            wait(&istatus);
            printf("parent is killed.\n");
            exit(0);
        }
        else  //子进程2
        {
            signal(17,signal_test5_changevalue);  //SIGCHLD
            printf("child2 id is %d\n",getpid());
            while(wait_flag == 1);
            printf("child2 is killed\n");
            exit(0);
        }
    }
    else  //子进程1
    {
        signal(16,signal_test5_changevalue);  //SIGSTKFLT
        printf("child1 id is %d\n",getpid());
        while(wait_flag == 1);
        printf("child1 is killed\n");
        exit(0);
    }
}

void signal_test5_changevalue(int)
{
    wait_flag = 0;
    printf("pid: %d, wait_flag = 0\n",getpid());
}

void signal_test5_stop(int)
{
    printf("process %d: stop info!\n",getpid());
}









































