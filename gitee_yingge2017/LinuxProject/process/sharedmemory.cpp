#include "sharedmemory.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

void sharedmemory_test()
{
    shm_test();
}

void shm_test()
{
    pid_t pid=fork();
    if(pid<0){
        perror("fork");
        return;
    }
    if(pid==0){
        shm_test_write();
        exit(0);
    }

    sleep(1);
    shm_test_read();
    wait(NULL);
    return;
}

void shm_test_write()
{
    int fd=shm_open("region",O_CREAT|O_RDWR,S_IRUSR|S_IWUSR);
    if(fd<0){
        perror("shm_open");
        return;
    }
    ftruncate(fd,10);
    char *ptr=(char*)mmap(NULL, 10,  PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr==MAP_FAILED){
        perror("mmap");
        return;
    }
    *ptr=0x12;
    for(int i=0;i<10;i++){
        *ptr=0x1*i;
        sleep(1);
        printf("write:%d\n",*ptr);
    }
    return ;
}

void shm_test_read()
{
    int fd=shm_open("region",O_CREAT|O_RDWR,S_IRUSR|S_IWUSR);
    if(fd<0){
        perror("shm_open");
        return;
    }
    ftruncate(fd,10);
    char *ptr=(char*)mmap(NULL, 10,  PROT_READ , MAP_SHARED, fd, 0);
    if(ptr==MAP_FAILED){
        perror("mmap");
        return;
    }
    while(*ptr!=0x9){
        printf("read:%d\n",*ptr);
        sleep(1);
    }

    printf("%s_ptr:%d\n",__func__,*ptr);
}
