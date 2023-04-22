/*
    #include <unistd.h>

    extern char **environ;

    int execl(const char *pathname, const char *arg, ...);
    int execlp(const char *file, const char *arg, ...);
        会到环境变量中查找可执行文件，如果找到了就执行，找不到就执行不成功
        - 参数：
            - path：需要指定的执行的文件的文件名
                a.out
                ps
            - arg：是执行可执行文件需要的参数列表
                - arg0：第一个参数没有什么作用，为了方便，一般写的是可执行程序的名称
                - arg1：程序执行需要的参数列表
                - arg2：程序执行需要的参数列表
                。。。
                - argn：程序执行需要的参数列表，最后需要以NULL结束（哨兵）
        - 返回值：
            - 成功：不会返回
            - 失败：返回-1
            - errno：存储错误信息
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    // 创建一个子进程，在子进程执行exec函数族中的函数
    pid_t pid = fork();
    if(pid>0)
    {
        printf("i am parent process, pid: %d\n", getpid());
    }
    else if (pid == 0)
    {
        // execl("hello", "hello", NULL);
        execlp("ps", "ps", "aux", NULL);
        printf("i am child process, pid: %d\n", getpid());

    }
    for (int i = 0; i < 3; i++)
    {
        printf("i = %d, pid: %d\n", i, getpid());
    }
    
    
    return 0;
}