/*
    #include <sys/types.h>
    #include <sys/wait.h>

    pid_t waitpid(pid_t pid, int *wstatus, int options);
        功能：等待（回收）指定进程好的子进程，可以设置是否阻塞。
        参数：
            - pid_t pid：指定的进程号
                - pid > 0：等待指定进程号的子进程
                - pid = 0：等待和调用进程**同组**的任意子进程
                - pid = -1：等待任意子进程
                - pid < -1：等待和调用进程**同组**的任意子进程
            - int * wstatus：进程退出时的状态信息、传入的是一个int类型的地址，传出参数
            - int options：选项
                - 0 阻塞
                - WNOHANG：如果没有子进程结束，不阻塞，立即返回0
                - WUNTRACED：如果子进程被暂停，也返回

        返回值：
            - >0：返回被回收的子进程的pid
            - =0：options=WNOHANG，没有子进程结束
            - =-1（没有子进程结束，或者系统错误）

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
    if (pid > 0)
    {
        // 父进程
        while (1)
        {
            printf("parent pid = %d\n", getpid());

            int st;

            // int ret = wait(NULL); // 父进程等待子进程结束，如果子进程没有结束，父进程会被阻塞
            int ret = waitpid(-1, &st, WNOHANG); // 父进程等待子进程结束，如果子进程没有结束，父进程会被阻塞
            sleep(1);

            if (ret == -1)
            {
                break;
            }

            if(ret == 0)
            {
                continue;
            }
            else if(ret > 0)
            {
                
                if (WIFEXITED(st))
                {
                    printf("退出的状态码：%d\n", WEXITSTATUS(st));
                }
                if (WIFSIGNALED(st))
                {
                    printf("被哪个信号干掉了：%d\n", WTERMSIG(st));
                }

                printf("child die, pid = %d\n", ret);
            }
            

        }
    }
    else if (pid == 0)
    {
        // 子进程
        while (1)
        {
            printf("child pid = %d\n", getpid());
            sleep(1);
        }
        exit(1);
        int a  = 1;
        size_t b = a;
        long long c = 1;
        size_t d = c;
    }

    return 0;
}