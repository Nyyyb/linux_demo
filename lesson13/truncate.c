/*
    #include <unistd.h>
    #include <sys/types.h>

    int truncate(const char *path, off_t length);
        作用：缩减或者扩展文件的尺寸到指定的大小
        参数：
            - path：要修改的文件的路径
            - length：需要最终文件变成的大小
*/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{

    int ret = truncate("b.txt", 20);
    if(ret == -1)
    {
        perror("truncate error");
        return -1;
    }

    return 0;
}