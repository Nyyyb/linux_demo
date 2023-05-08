#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid = fork();
    // 判断是父进程还是子进程
    if(pid>0)
    {
        // 父进程
        printf("parent pid = %d, child pid = %d\n", getpid(), pid);
        printf("my parent pid = %d\n", getppid());
       
    }
    else if(pid == 0)
    {
        sleep(1); 
        // 子进程
        printf("child pid = %d, parent pid = %d\n", getpid(), getppid());
       
    }
    for(int i = 0 ; i < 3; i++)
    {
        printf("i = %d, pid: %d\n", i, getpid());
        // sleep(1);
    }
    

    return 0;
}