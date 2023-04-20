/*
    #include <unistd.h>

    int chdir(const char *path);
        作用：修改进程的工作目录
            比如在/home/nyyyb启动了一个可执行程序a.out，进程的工作目录就是/home/nyyyb
        参数
            - path：要修改的工作目录的路径

    #include <unistd.h>

    char *getcwd(char *buf, size_t size);
        作用：获取当前的工作目录
        参数：
            - buf：存储的路径，指向一个数组（传出参数）
            - size：数组的大小

        返回值：
            返回的指向的一块内存，这个数据就是第一个参数

*/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    char dirbuf[128] = {0};
    getcwd(dirbuf, sizeof(dirbuf) / sizeof(dirbuf[0]));
    printf("当前的工作目录是：%s\n", dirbuf);

    // 修改工作目录
    int ret = chdir("/home/nyyyb/linux_demo/lesson13");
    if (ret == -1)
    {
        perror("chdir error");
        return -1;
    }
    // 创建一个新的文件
    int fd = open("c.txt", O_CREAT | O_RDWR, 0777);
    if (fd == -1)
    {
        perror("open error");
        return -1;
    }

    char dirbuf1[128] = {0};
    getcwd(dirbuf1, sizeof(dirbuf1) / sizeof(dirbuf1[0]));
    printf("%ld\n", sizeof(dirbuf1) / sizeof(dirbuf1[0]));
    printf("当前的工作目录是：%s\n", dirbuf1);

    close(fd);
    return 0;
}