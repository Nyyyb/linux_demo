/*
    #include <signal.h>
    int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
        - 功能：将自定义信号集中的数据设置到内核中（设置阻塞，解除阻塞，替换）
        - 参数：
            - how：如何对内核阻塞信号进行处理
                - SIG_BLOCK：将用户设置的阻塞信号添加到内核中，内核中原来的数据不变
                    假设内核中默认的阻塞信号是mask mask | set
                - SIG_UNBLOCK：根据用户设置的数据。对内核中的数据进行解除阻塞
                    信号集中的数据是mask mask & ~set，set中需要解除的设为1，不需要解除的设为0                    
                - SIG_SETMASK：将自定义信号集中的信号设置到内核阻塞信号集中
            - set: 已经初始化好的用户自定义信号集
            - oldset：保存设置之前的内核中的阻塞信号集的状态，可以是NULL
        - 返回值：
            成功 0
            失败 -1 errno
                EFAULT
                EINVAL

    int sigpending(sigset_t *set);
        - 功能：获取内核中的未决信号集
        - 参数：
            - set：传出参数，保存获取到的未决信号集
        - 返回值：
            0成功
            -1失败 errno
                EFAULT
                EINVAL


*/

// 编写一个程序，把所有的常规信号（1-31）的未决状态打印到屏幕


#include <stdio.h>
#define __USE_POSIX 1
#include <signal.h>
#include <bits/types/sigset_t.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    sigset_t set;
    sigemptyset(&set);
    
    // 将2号和3号信号添加到信号集中
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    // 修改内核中的阻塞信号集，这是全部阻塞了？？？
    sigprocmask(SIG_BLOCK, &set, NULL);
    int num = 0;
    while (1)
    {   
        num++;
        sigset_t pendingSet;
        // 获取当前的未决信号集的数据
        sigemptyset(&pendingSet);
        sigpending(&pendingSet);

        // 遍历前32位
        for(int i = 1; i <= 32; i++)
        {
            if(sigismember(&pendingSet, i))
            {
                printf("1");
            }
            else if(!(sigismember(&pendingSet, i)))
            {
                printf("0");
            }
            else
            {
                perror("sigismember error");
                exit(0);
            }
            
        }
        printf("\n");
        sleep(1);
        if(num == 10)
        {
            // 解除阻塞
            sigprocmask(SIG_UNBLOCK, &set, NULL);
        }
    }
    


    
}