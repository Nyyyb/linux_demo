/*

    #include <stdlib.h>
    void exit(int status);

    #include <unistd.h>
    void _exit(int status);

    status参数：进程退出时的一个状态信息，父进程回收子进程资源的时候可以获取

    
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("hello\n");
    // 数据在IO缓冲区，\n可以刷新IO缓冲区
    printf("world");

    exit(0);
    _exit(0);

    return 0;
}