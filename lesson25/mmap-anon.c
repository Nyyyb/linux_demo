/*
    匿名映射：不需要文件实体进行内存映射
    之前没关系的进程进行通信就是因为有文件，所以也可以叫文件映射
*/
// #define __USE_MISC

#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    // 1. 创建匿名内存映射区
    int length = 4096;
    void * ptr = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    // MAP_SHARED和MAP_ANONYMOUS不冲突，shared是映射区数据变了会更改到磁盘，private是不更改
    // anonymous所以指定fd=-1
    if(ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(0);
    }

    // 父子进程间通信
    pid_t pid = fork();
    if(pid >0)
    {
        // 父进程
        strcpy((char *)ptr, "hello");
        wait(NULL);
    }
    else if(pid == 0)
    {
        // 子进程
        sleep(1);
        // 非阻塞，父进程还没有执行，子进程就执行完了，子进程就读不到了
        // char * buf[1024] = {0};
        // strcpy(buf, (char*)ptr);
        // printf("buf : %s\n", buf);
        printf("%s\n", (char *)ptr);
    }

    // 释放内存映射区
    int ret = munmap(ptr, length);
    if(ret == -1)
    {
        perror("munmap");
        exit(0);
    }
    return 0;
}
