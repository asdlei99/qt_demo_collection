#include "fork_test.h"
#include <stdlib.h>
#include "error.h"
#include "unistd.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/*通过输出发现，count在两个线程中分别记数，互不影响。
*/
void fork_test()
{
    int count=0;
    pid_t pid=fork();
    if(pid==-1){
        perror("Fork failed");
        return;
    }
    else if(pid>0){//父进程，pid保存的是子进程的进程号。
        int status=0;
        waitpid(pid,&status,0);

        while(1){
            printf("This is parent:%d,count:%d\n",getpid(),count++);
            sleep(1);
            if(count==5)
                break;
        }
        printf("child exit by code:%d\n",WEXITSTATUS(status));
    }
    else if(pid==0){
        while(1){
            printf("This is child:%d,count:%d\n",getpid(),count++);
            sleep(1);

            if(count==5)
                exit(99);
        }
    }
}

void fork_test_multi_child()
{
    const int BuffSize=100;
    char buf[BuffSize]={0};

    const int ChildNum=3;
    int pidArray[ChildNum]={0};

    int pfd[2];

    if(pipe(pfd)==-1){
        perror("pipe failed");
        return;
    }

    pid_t  pid;
    for(int i=0;i<ChildNum;++i){
        switch ((pid=fork())) {
        case -1:
            perror("fork failed");
            return;
            break;
        case 0://child
            if(close(pfd[0])){//close read pipe.
                perror("Child close pfd[0] failed");
                return;
            }

            //子进程任务
            for(int i=0;i<5;++i){
                printf("Child:%d,%d\n",getpid(),i);
                sleep(1);
            }

            //            int statuscode=0;
            //            if(write(pfd[1],&statuscode,sizeof(statuscode))==-1){
            //                perror("Child write failed");
            //            }

            printf("Child %d,exit.\n",getpid());
            exit(9);

            break;
        default:
            pidArray[i]=pid;
            break;
        }
        sleep(1);
    }
    //parent job
    if(close(pfd[1])){ //Parent close write pipe.
        perror("Parent close pfd[1]");
    }

    int tmppid=-1;
    int statuscode=-1;
    int childcount=0;
    //父进程不断轮询监视。
    while(1){
        if(childcount==3){
            printf("Parent exit,childcount==3.\n");
            exit(0);
        }

        //wait默认阻塞
        if(tmppid=wait(&statuscode)){
            if(tmppid<=0)
                continue;
            //拿到退出的进程的pid，获取exitcode.
            for(int i=0;i<ChildNum;++i){
                if(pidArray[i]==-1)
                    continue;
                if(pidArray[i]==tmppid){
                    int exitcode=WEXITSTATUS(statuscode);
                    printf("Parent:Child %d,exit code %d\n",tmppid,exitcode);

                    pidArray[i]=-1;

                    ++childcount;
                }
            }
        }
    }

    printf("Parent exit.\n");
    exit(0);
}

void fork_test_manager()
{
    fork_test_multi_child();
}
