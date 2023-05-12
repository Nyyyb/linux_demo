/*
    #include <signal.h>

    typedef void (*sighandler_t)(int);

    sighandler_t signal(int signum, sighandler_t handler);
        - 功能：设置某个信号的捕捉行为
        - 参数：
            - signum: 要捕捉的信号，除了9SIGKILL，一般采用宏值
            - handler: 捕捉信号要如何处理
                - SIG_IGN: 忽略信号
                - SIG_DFL: 默认处理方式
                - 回调函数：这个函数是内核调用的，程序只负责写，捕捉到信号如何处理信号
                    回调函数：
                        - 程序员实现，提前准备好的，函数的类型根据实际需求，看函数指针的定义
                        - 不是程序员调用的，当信号产生由内核调用
                        - 函数指针是实现回调的手段，函数实现后，将函数名放到函数指针的位置就好了
        - 返回值：
            - 成功返回上一次注册的回调函数地址
            - 失败SIG_ERR，设置errno

    SIGKILL SIGSTOP不能被捕捉，不能被忽略

*/

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>

void sigalrm_handler(int signo)
{
    printf("捕捉到了SIGALRM信号，编号是：%d\n", signo);
}

int main()
{
    // 注册信号捕捉
    // signal(SIGALRM, SIG_IGN);
    // signal(SIGALRM, SIG_DFL);

    // typedef void (*sighandler_t)(int);  函数指针

    signal(SIGALRM, sigalrm_handler);

    struct itimerval new_value;

    // 设置间隔时间
    new_value.it_value.tv_sec = 10;  // 延迟10秒
    new_value.it_interval.tv_sec = 2;   // 每隔2秒

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
    getchar();

    return 0;
}
