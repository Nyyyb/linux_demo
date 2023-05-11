// 1秒钟，电脑能数多少个数
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/*
    实际的时间 = 内核时间+用户时间+IO等消耗的时间
    进行文件IO操作比较浪费时间
    系统调用如alarm要切换到内核

    定时器，与进程的状态无关（自然定时法）。无论进程处于什么状态，alarm都会计时
*/

int main()
{

    int i = 0;
    int fd = open("./test.txt", O_RDWR | O_APPEND | O_CREAT, 0777);
    // FILE * fs = fopen("test.txt", "a");
    if(fd ==-1)
    {
        perror("open error");
        return -1;
    }
    int seconds = alarm(1);
    char buf[4];
    while(1)
    {
        i++;
        // fprintf(fs, "%d\n", i);    // 快
        int len = sprintf(buf, "%d\n", i);   // 比dprintf快
        if(len < 0 )  
        {
            perror("sprintf");
            return -1;
        }
        // dprintf(fd, "%d\n", i);     // 慢
        write(fd, buf, len);
        // printf("%d\n", ++i);
    }
    
    return 0;
}