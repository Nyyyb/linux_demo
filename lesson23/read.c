// 从管道读数据
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main()
{
    // 1. 打开管道文件
    int fd = open("test", O_RDONLY);
    if(fd == -1)
    {
        perror("open");
        exit(0);
    }

    // 读数据
    while (1)
    {
        char buf[1024] = {0};
        int len = read(fd, buf, sizeof(buf));
        if(len == 0)
        {
            printf("写端断开连接。。。\n");
            // exit(0);
            // break;
            continue;
            
        }
        printf("recv buf : %s\n", buf);
    }
#if 0 
    // char str[10] = "hello";
    // printf("strlen: %ld\n", strlen(str));
    // printf("sizeof: %ld\n", sizeof(str));

    // char str_cn[4] = "汉";
    // printf("strlen: %ld\n", strlen(str_cn));
    // printf("sizeof: %ld\n", sizeof(str_cn));
#endif

    close(fd);
    return 0;
}