#include "forktest.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#if 0
forktest::forktest()
{

}

//void fork_test_manager()
//{
//    fork_test();
//}

void fork_test()
{
    pid_t pid;

    pid=fork();
    if(pid==-1){
        perror("fork failed");
        return;
    }
    else if(pid>0){  //父进程，返回的是子进程的pid.
        printf("This is parent,pid:%d.\n",getpid());
        /*status 不是NULL时,子进程的结束状态值会由参数 status 返回，而子进程的进程识别码作为函数返回值返回。
         * 调用 wait 函数时,调用进程将会出现下面的情况:
        * 如果其所有子进程都还在运行,则阻塞。
        *如果一个子进程已经终止,正等待父进程获取其终止状态,则获取该子进程的终止状态然后立即返回。
        *如果没有任何子进程,则立即出错返回。
        *
        * 返回值是返回进程的进程号,错误返回-1。
         */
        sleep(1);
        int status;
        pid_t pid=wait(&status);
        if(pid==-1)
            perror("Get pid failed");
        else{
            //获取子进程退出时的值。
            int childExitCode=WEXITSTATUS(status);
            printf("Parent get child %d exit status:%d.\n",pid,childExitCode);
        }

        exit(0);
    }
    else if(pid==0){ //子进程
        printf("This is child,pid:%d.\n",getpid());
        sleep(3);
        exit(9);
    }
}
#endif
