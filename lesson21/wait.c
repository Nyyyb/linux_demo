/*
    #include <sys/types.h>
    #include <sys/wait.h>

    pid_t wait(int *wstatus);
        功能：等待任意一个子函数结束，如果任意一个子进程结束了，此函数会回收子进程的资源
        参数：
            - int * wstatus：进程退出时的状态信息、传入的是一个int类型的地址，传出参数
        返回值：
            - 成功：返回被回收的子进程的pid
            - 失败：返回-1（没有子进程结束，或者系统错误）
        调用wait函数的进程会被挂起（阻塞），直到他的一个子进程推出或者收到一个不能被忽略的信号
        才被唤醒（相当于继续往下执行），如果没有子进程了会立刻返回-1；如果子进程都已经结束了，
        也会立即返回
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    for (int i = 0; i < 5; i++)
    {
        pid = fork(); // 创建子进程 子进程fork以后会返回0，不会继续创建孙子进程 
        if (pid == 0)
        {
            break;
        }
    }
    if(pid > 0)
    {
        // 父进程
        while(1)
        {
            printf("parent pid = %d\n", getpid());

            int st;

            // int ret = wait(NULL); // 父进程等待子进程结束，如果子进程没有结束，父进程会被阻塞
            int ret = wait(&st); // 父进程等待子进程结束，如果子进程没有结束，父进程会被阻塞
            
            if( ret== -1)
            {
                break;
            }
            if(WIFEXITED(st))
            {
                printf("退出的状态码：%d\n", WEXITSTATUS(st));
            }
            if(WIFSIGNALED(st))
            {
                printf("被哪个信号干掉了：%d\n", WTERMSIG(st));
            }


            printf("child die, pid = %d\n", ret);


            sleep(1);
        }
    }
    else if(pid == 0)
    {
        // 子进程
        while(1)
        {
            printf("child pid = %d\n", getpid());
            sleep(1);
        }
        exit(1);
    }

    return 0;
}