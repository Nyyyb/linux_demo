/*
    #include <signal.h>
    * int sigemptyset(sigset_t *set);
        - 功能：清空信号集当中的数据，将信号集中所有的标志位置为0
        - 参数:set 传出参数，需要处理的信号集
        - 返回值:
            - 成功：0
            - 失败：-1，设置errno
    * int sigfillset(sigset_t *set);
        - 功能：将信号集中的所有标志位置为一
        - 参数：set 传出参数，需要处理的信号集
        - 返回值：
            - 成功：0
            - 失败：-1，设置errno
    * int sigaddset(sigset_t *set, int signum);
        - 功能：设置信号集中的某一个信号对应的标志位为1
        - 参数：
            - set 传出参数，需要处理的信号集
            - signum 要设置的信号
        - 返回值：
            - 成功：0
            - 失败：-1，设置errno
    * int sigdelset(sigset_t *set, int signum);
        - 功能：设置信号集中的某一个信号对应的标志位为0
        - 参数：
            - set 传出参数，需要处理的信号集
            - signum 要设置的信号
        - 返回值：
            - 成功：0
            - 失败：-1，设置errno
    * int sigismember(const sigset_t *set, int signum);
        - 功能：判断信号集中的某一个信号对应的标志位是否为1，是否阻塞
        - 参数：
            - set const不能修改，需要处理的信号集
            - signum 要设置的信号
        - 返回值：
            - 1：是
            - 0：不是
            - -1：设置errno
    *  
    * 
    * 
*/
#include <stdio.h>
#define __USE_POSIX
#include <signal.h>
#include <stdlib.h>

int main()
{
    sigset_t set;
    sigemptyset(&set);  // 清空信号集

    // 判断SIGINT是否在信号机set里面
    int ret = sigismember(&set, SIGINT);
    if(ret == 1)
    {
        printf("在\n");
    }
    else if(ret == 0)
    {
        printf("不在\n");
    }
    else
    {
        perror("sigismember error");
        exit(0);
    }
    // 添加几个信号到信号集中
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    ret = sigismember(&set, SIGINT);
    if(ret == 1)
    {
        printf("在\n");
    }
    else if(ret == 0)
    {
        printf("不在\n");
    }
    else
    {
        perror("sigismember error");
        exit(0);
    }

    // 删除信号
    sigdelset(&set, SIGQUIT);
    ret = sigismember(&set, SIGQUIT);
    if(ret == 1)
    {
        printf("在");
    }
    else if(ret == 0)
    {
        printf("不在");
    }
    else
    {
        perror("sigismember error");
        exit(0);
    }
    
    return 0;
}