/*
    #include <sys/types.h>
    #include <signal.h>

    int kill(pid_t pid, int sig);
        - 功能：给某个进程发送信号
        - 参数
            - pid：进程ID
                >0：发送给指定进程
                =0: 发送给当前进程所在进程组的所有进程
                =-1: 发送给每一个有权限接受这个信号的进程 
                    发送给除1号进程和自己以外的所有进程
                <-1: 发送给指定进程组的所有进程，进程组号为pid绝对值
            - sig：信号编号（信号的编号如9）或者是宏值（信号的名称如SIGKILL）

        kill(getppid(), SIGKILL);
        kill(getppid(), 9);
        - 返回值：0
            errno
    int raise(int sig);
        功能：给当前进程发送信号
        参数：信号编号或者是宏值
        返回值:
            0成功
            非0失败
        kill(getpid(), SIGKILL);
    void abort(void);
        - 功能：发送SIGABRT信号给当前进程，杀死当前进程
        kill(getpid(), SIGABRT);

*/


#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if(pid > 0)
    {
        // 父进程
        printf("parent process\n");
        sleep(2);
        printf("parent process kill child process\n");
        kill(pid, SIGKILL);
    }
    else if(pid == 0)
    {
        // 子进程
        int i = 0;
        for(i = 0; i < 5; i++)
        {
            printf("child process\n");
            sleep(1);
        }
    }

    return 0;
}