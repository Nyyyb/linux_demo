#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    // 1. 判断有名管道是否存在
    int ret = access("fifo1", F_OK);
    if(ret == -1)
    {
        // 文件不存在
        printf("管道不存在，创建对应的有名管道\n");
        int ret = mkfifo("fifo1", 0664);
        if(ret == -1)
        {
            perror("mkfifo");
            exit(0);
        }
    }

    ret = access("fifo2", F_OK);
    if(ret == -1)
    {
        // 文件不存在
        printf("管道不存在，创建对应的有名管道\n");
        int ret = mkfifo("fifo2", 0664);
        if(ret == -1)
        {
            perror("mkfifo");
            exit(0);
        }
    }
    // 2. 以只写的方式打开管道1
    int fdw = open("fifo1", O_WRONLY);
    if (fdw == -1)
    {
        perror("open");
        exit(0);
    }

    printf("打开fifo1成功，等待写入数据...\n");
    // 3. 以只读的方式打开管道2
    int fdr = open("fifo2", O_RDONLY);
    if (fdr == -1)
    {
        perror("open");
        exit(0);
    }

    printf("打开fifo2成功，等待读取...\n");

    char buf[128];

    // 4. 循环的写读数据
    while (1)
    {
        memset(buf, '0', sizeof(buf));
        // 获取标准输入的数据
        fgets(buf, 128, stdin);
        // 写数据
        int ret = write(fdw, buf, sizeof(buf));
        if(ret == -1)
        {
            perror("write");
            break;
        }

        // 5. 读管道数据
        memset(buf, 0, sizeof(buf));
        ret = read(fdr, buf, sizeof(buf));
        if(ret <= 0)
        {
            perror("read");
            break;
        }
        printf("buf : %s\n", buf);

    }
    

    close(fdw);
    close(fdr);
    return 0;
}