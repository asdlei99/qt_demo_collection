#include "pipe_test.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void pipe_test_manager()
{
    pipe_test();
}

void pipe_test()
{
#if 1
    const int BuffSize=2;
    char buf[BuffSize]={0};
    int num=0;
    int pfd[2];		//管道描述符

    //0 read,1 write
    if(pipe(pfd)==-1){	//打开管道
        perror("Pipe failed");
        return;
    }

    switch(fork()){
    case -1:
        perror("Fork failed");
        return;break;
    case 0: //子进程
        if(close(pfd[1])==-1){		//写端
            perror("Child close pfd[1] failed");
            return;
        }

        printf("Child pid:%d \n",getpid());

        printf("Child read from pfd[0]:");
        fflush(stdout);

        for(;;){//子进程在读端不断的读取数据,直到EOF。
            num=read(pfd[0],buf,BuffSize);	//从读端读取数据
            buf[num]='\0';			//

            if(num==-1){
                perror("Chid read from pfd[0] failed");
                return;
            }
            if(num==0)//读取到文件的结束标识,没有读取到数据
                break;

            //            printf("Child read from pfd[0]:");
            //            fflush(stdout);
            if(write(STDOUT_FILENO,buf,BuffSize)==-1){ //向终端输出
                perror("Child write failed");
                return;
            }
        }

        printf("\n");
        if(close(pfd[0])==-1){		//关闭读端
            perror("Child close pfd[0] faild");
            return;
        }
       // printf("Child exit with code:99.\n");
        //        exit(99);
        break;

    default://parent 父进程
        if(close(pfd[0])==-1){		//关闭读端
            perror("Parent close pfd[1] failed");
            return;
        }

        printf("Parent pid:%d \n",getpid());

        const char *str="Hello,This is parent process.";
        int len=strlen(str);
        if(len!=write(pfd[1],str,len)){		//向写端写数据
            perror("Parent write failed");
            return;
        }

        if(close(pfd[1])==-1){ //父进程关闭管道的写端后，子进程在读取读端的时候会读到EOF
            perror("Parent close pfd[1] failed");
            return;
        }

        int status=-1;
        wait(&status);		//阻塞进程，直到子进程退出
        pid_t pid = -1;
        pid = wait(&status);
        printf("Parent:wait pid:%d \n",pid);

        int childExitCode=WEXITSTATUS(status); 		//子进程是否正常退出，如果正常退出则返回非零值
        printf("Parent:child exit code:%d.\n",childExitCode);

        exit(0);
        break;
    }
#endif

}
