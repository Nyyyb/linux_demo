/*
    #include <sys/time.h>

    int getitimer(int which, struct itimerval *curr_value);
    int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);
        - 功能：设置定时器（闹钟），可以替代alarm，精度更高（us），可以周期性定时
        - 参数：
            - which: 定时器以什么时间计时
                ITIMER_REAL: 真实时间，时间到达，发送SIGALRM信号   常用
                ITIMER_VIRTUAL：用户时间，时间到达，发送SIGVTALRM
                ITIMER_PROF：该进程在用户态和内核态所消耗的时间来计时，时间到达发送SIGPROF信号
            - new_value: 设置定时器的属性
            struct itimerval {              // 定时器结构体
               struct timeval it_interval; //Interval for periodic timer 每个多长时间
               struct timeval it_value;    // Time until next expiration 延长多长时间执行定时器
            };

            struct timeval {                // 时间结构体
                time_t      tv_sec;         // seconds
                suseconds_t tv_usec;        // microseconds
            };

            10秒后it_value每隔两秒定时一次it_interval
            - old_value : 记录上一次定时的时间参数 NULL 一般不使用
        - 返回值：
            - 0成功
            - -1失败，perror

*/
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

int main()
{
    struct itimerval new_value;
    new_value.it_value.tv_sec = 10;  // 延迟10秒
    new_value.it_interval.tv_sec = 2;   // 每隔2秒

    // 微秒的如果不设置就是随机的值，所以要设置为0
    new_value.it_value.tv_usec = 0;
    new_value.it_interval.tv_usec = 0;

    int ret =setitimer(ITIMER_REAL, &new_value, NULL);  // 非阻塞
    printf("定时器开始了");
    if(ret == -1)
    {
        perror("setitimer error");
        exit(0);
    }
    getchar();

    return 0;
}
