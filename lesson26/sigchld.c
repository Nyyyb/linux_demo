/*
    SIGCHILD信号产生的三个条件
        1 子进程终止时
        2 子进程接收到SIGSTOP信号停止时
        3 子进程处在停止态，接受到SIGCONT后唤醒时
    使用SIGCJHLD解决僵尸进程问题
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#define __USE_POSIX 1
#include <signal.h>
#include <sys/wait.h>

void myFunc(int signo)
{
    printf("捕捉到的信号：%d\n", signo);    
    // 回收子进程资源
    // while(1)
    // {
    //     wait(NULL);
    // }
    while (1)
    {
        int ret = waitpid(-1, NULL, WNOHANG);
        if(ret > 0)
        {
            printf("child die, pid = %d\n", ret);
        }
        else if(ret == 0)
        {
            // 说明还有子进程活着
            break;
        }
        else if(ret == -1)
        {
            // 没有子进程
            break;
        }
        
    }
    
}

int main()
{
    // 提前设置好阻塞信号集，阻塞SIGCHLD
    // 因为有可能子进程很快结束，父进程还没有注册完信号捕捉
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);

    

    // 创建一些子进程
    pid_t pid;
    for(int i = 0; i < 20; i++)
    {
        pid = fork();
        if(pid == 0)
        {
            break;
        }
    }
    
    // 父进程
    if(pid >0)
    {
        // 父进程一直在运行，子进程先死了，父进程没有回收资源，产生僵尸进程
        // 捕捉子进程死亡时发送的SIGCHLD信号
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = myFunc;
        sigemptyset(&act.sa_mask);
        act.sa_restorer = NULL;
        // 注册信号捕捉
        // 但是如果信号捕捉还没有注册完，子进程就全部结束了，就会报错
        sigaction(SIGCHLD, &act, NULL);
        
        // 注册完信号捕捉后，解除阻塞
        sigprocmask(SIG_UNBLOCK, &set, NULL);

        while(1)
        {
            printf("parent pid = %d\n", getpid());
            sleep(2);
        }
    }
    // 子进程
    else if(pid ==0)
    {
        printf("child pid = %d\n", getpid());
    }

    return 0;
}