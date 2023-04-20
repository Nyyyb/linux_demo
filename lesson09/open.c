/*

    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    // 打开一个已经存在的文件
    int open(const char *pathname, int flags);
        参数：
            - pathname：要打开的文件路径
            - flags：对文件的操作权限设置还有其他设置
                O_RDONLY：只读
                O_WRONLY：只写
                O_RDWR：读写
                这三个是互斥的

        返回值：返回一个新的文件描述符，如果失败返回-1

    errno：属于Linux系统函数库，库里面的一个全局变量，记录的是最近的错误号

     #include <stdio.h>

    void perror(const char *s);作用：打印errno对应的错误描述
        s参数：用户描述，比如hello，最终的输出内容是hello:xxx（实际的错误描述）

    // 创建一个新的文件
    int open(const char *pathname, int flags, mode_t mode);

*/

#include <sys/types.h>  // open()
#include <sys/stat.h>   // open()
#include <fcntl.h>      // open()
#include <stdio.h>      // perror()
#include <unistd.h>     // close()

int main()
{
    int fd = open("a.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return -1;
    }

    // 关闭
    close(fd);

    return 0;
}
