/*
    #include <signal.h>
    int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
        - 功能：检查或者改变信号的处理，信号捕捉
        - 参数：
            - signum
            - act：捕捉到信号之后的处理动作
            - oldact：一般不使用，NULL

        - 返回值
            - 成功：0
            - 失败：-1，设置errno

    struct sigaction {
        // 函数指针，指向的函数就是信号被捕获到的处理函数
        void     (*sa_handler)(int);
        // 不常用
        void     (*sa_sigaction)(int, siginfo_t *, void *);
        // 信号集 掩码，临时阻塞信号集，临时阻塞某些信号
        sigset_t   sa_mask;
        // 指定第一个sa_handler还是第二个sa_sigaction处理：0，第一个；SA_SIGINFO，第二个
        int        sa_flags;
        // 被废弃了 NULL
        void     (*sa_restorer)(void);
    };

*/

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#define __USE_POSIX 1
// #define __USE_MISC 1
#include <signal.h>

void sigalrm_handler(int signo)
{
    printf("捕捉到了SIGALRM信号，编号是：%d\n", signo);
}

int main()
{
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = sigalrm_handler;
    sigemptyset(&act.sa_mask);

    // 注册信号捕捉
    sigaction(SIGALRM, &act, NULL);

    struct itimerval new_value;

    // 设置间隔时间
    new_value.it_value.tv_sec = 1;  // 延迟10秒
    new_value.it_interval.tv_sec = 1;   // 每隔2秒

    // 微秒的如果不设置就是随机的值，所以要设置为0
    new_value.it_value.tv_usec = 0;
    new_value.it_interval.tv_usec = 0;

    int ret =setitimer(ITIMER_REAL, &new_value, NULL);  // 非阻塞
    printf("定时器开始了\n");
    if(ret == -1)
    {
        perror("setitimer error");
        exit(0);
    }
    // getchar();
    while (1)
    {
        /* code */
    }
    

    return 0;
}