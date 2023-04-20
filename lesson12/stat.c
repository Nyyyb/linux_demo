/*
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>

    int stat(const char *pathname, struct stat *statbuf);
        作用：获取一个文件相关的一些信息
        参数：
            - pathname
            - statbuf：结构体变量，传出参数
        返回值：
            成功：0
            失败：-1，errno
    int lstat(const char *pathname, struct stat *statbuf);

        参数：
            - pathname
            - statbuf：结构体变量，传出参数
        返回值：
            成功：0
            失败：-1，errno
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    struct stat statbuf1, statbuf2;
    int ret1 = stat("b.txt", &statbuf1);
    if(ret1 == -1)
    {
        perror("status");
        return -1;
    }

    printf("size: %ld\n", statbuf1.st_size);
    int ret2 = lstat("b.txt", &statbuf2);
    if(ret2 == -1)
    {
        perror("lstat");
        return -1;
    }
    printf("size: %ld\n", statbuf2.st_size);

    return 0;
}