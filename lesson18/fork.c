/*
    #include <sys/types.h>
    #include <unistd.h>

    pid_t fork(void);
        作用：用于创建子进程
        返回值：
            会返回两次
            - 失败：返回-1
            - 在父进程中：返回子进程的pid
            - 在子进程中：返回0
            如何区分父进程和子进程：通过fork的返回值
            在父进程中返回-1表示创建子进程失败

*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int num = 10;
    pid_t pid = fork();
    // 判断是父进程还是子进程
    if(pid>0)
    {
        // 父进程
        printf("parent pid = %d, child pid = %d\n", getpid(), pid);
        // while(1);
        printf("parent num = %d\n", num);
        num+=10;
        printf("parent num += 10: %d\n", num);
    }
    else if(pid == 0)
    {
        // 子进程
        printf("child pid = %d, parent pid = %d\n", getpid(), getppid());
        // while(1);
        num+=100;
        printf("child num += 100: %d\n", num);
    }
    for(int i = 0 ; i < 3; i++)
    {
        printf("i = %d, pid: %d\n", i, getpid());
        // sleep(1);
    }
    sleep(10);

    return 0;
}