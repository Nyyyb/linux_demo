/*
    实现ps aux | grep xxx
    父子进程通信
    子进程：ps aux，子进程结束以后，将数据发送给父进程，
    父进程：获得到数据后过滤

    pipe()
    execlp()
    子进程将标准输出stdout_fileno重定向到管道的写端。dup2
*/

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int pipefd[2];
    int ret = pipe(pipefd);
    if(ret == -1)
    {
        perror("pipe");
        exit(0);
    }

    // 创建子进程
    pid_t pid = fork();
    if(pid>0)
    {
        // 父进程
        // 关闭写端
        close(pipefd[1]);

        // 从管道读取
        char buf[1024] = {0};
        int len = -1;
        while (len = read(pipefd[0], buf, sizeof(buf)-1)>0)
        {
            // 过滤数据输出
            printf("%s", buf);
            memset(buf, 0, 1024);
        }
        wait(NULL);

    }
    else if(pid == 0)
    {
        // 子进程
        // 关闭读端
        close(pipefd[0]);
        // 文件描述符的重定向，stdoud_fileno-> fd[1]
        dup2(pipefd[1], STDOUT_FILENO);
        // 写管道，执行ps aux
        execlp("ps", "ps", "aux", NULL);
        perror("execlp");
        exit(0);
    }
    else
    {
        perror("fork");
        exit(0);
    }
}
