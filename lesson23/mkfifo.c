/*
    创建fifo文件
    1. 通过命令：mkfifo 名字
    2. 通过函数

    #include <sys/types.h>
    #include <sys/stat.h>

    int mkfifo(const char *pathname, mode_t mode);
        参数：
            - pathname: 管道名称的路径
            - mode: 文件的权限，和open一样
                8进制

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    // 1. 判断文件是否存在
    int ret = access("test", F_OK);
    if(ret == -1)
    {
        printf("管道不存在，创建管道\n");

        // 2. 创建管道文件
        int ret = mkfifo("test", 0664);
        if(ret == -1)
        {
            perror("fifo");
            exit(0);
        }
    }
    
    


    return 0;
}