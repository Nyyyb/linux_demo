/*
    #include <unistd.h>

    unsigned int alarm(unsigned int seconds);
        功能：设置定时器，到达时间后发送一个SIGALARM信号给当前进程
        参数：定时器的时间，单位是秒
        返回值：
            - 之前没有定时器返回0
            - 之前有定时器，返回之前定时器剩余的时间
    
    - SIGALARM：默认终止当前进程，没一个进程都有且只有唯一的一个定时器，新的会覆盖旧的

    alarm()是不阻塞的
*/

#include <stdio.h>
#include <unistd.h>

int main()
{
    int seconds = alarm(5);
    printf("seconds = %d\n", seconds); // 0

    sleep(2);   
    seconds = alarm(3);
    printf("seconds = %d\n", seconds); // 3
    while(1)
    {

    }
    return 0;
}