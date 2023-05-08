/*
    #include <unistd.h>
    int pipe(int pipefd[2]);
        功能：创建一个匿名管道，用于匿名通信
        参数：int pipefd[2] 数组是一个传出参数
            pipefd[0]对应的是管道的读端
            pipefd[1]对应的是管道的写端
        返回值：
            成功，返回0
            失败，返回-1，errno

    管道默认是阻塞的，如果管道没有数据，那么read阻塞，如果管道满了，那么write阻塞

    注意：匿名管道只能用于具有关系的进程之间的通信（父子进程，兄弟进程）

*/

#include <unistd.h> // fork

#include <sys/types.h>

#include <stdio.h> // perror
#include <stdlib.h> // exit

#include <string.h>

#include <fcntl.h>

/*
    设置管道非阻塞
    int flags = fcntl(fd[0], F_GETFL); // 获取原来的flag
    flags |= O_NONBLOCK;    //修改flags的值
    // O_APPEND追加数据
    fcntl(fd[0], F_SETFL, flags);   // 设置新的flag
*/

// 子进程发送数据给父进程，父进程取到数据输出
int main()
{
    // 在fork之前创建管道
    int pipefd[2];
    int ret = pipe(pipefd);
    if(ret == -1)
    {
        perror("pipe");
        exit(0);
    }

    pid_t pid = fork();
    if (pid>0)
    {
        // 父进程
        // 从管道的读取端读取数据
        printf("i am parent process, pid : %d\n", getpid());

        int flags = fcntl(pipefd[0], F_GETFL); // 获取原来的flag
        flags |= O_NONBLOCK;    // 修改flags的值
        // O_APPEND追加数据
        fcntl(pipefd[0], F_SETFL, flags);   // 设置新的flag

        // 关闭写端
        close(pipefd[1]);
        char buf[1024] = {0};
        int i = 0;
        while (1)
        {
            int len = read(pipefd[0], buf, sizeof(buf));
            printf("parent recv : %s, len : %d, pid : %d\n", buf, len, getpid());
            memset(buf, 0, strlen(buf));
            sleep(1);
            size_t
        }
        
    }
    else if(pid == 0)
    {
        // sleep(10);
        // 子进程
        // 写数据
        printf("i am child process, pid : %d\n", getpid());
        // 关闭读端
        close(pipefd[0]);
        char buf[1024] = {0};
        while (1)
        {
            // 向管道写数据
            char *str = "汉";
            write(pipefd[1], str, strlen(str));
            sleep(5);
        }
        

    }
    

    return 0;
}