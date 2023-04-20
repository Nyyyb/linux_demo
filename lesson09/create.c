/*
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    int open(const char *pathname, int flags, mode_t mode);

        参数：
            - pathname：要创建的文件的路径
            - flags：对文件的操作权限设置还有其他设置
                操作权限是必选的
                O_RDONLY：只读
                O_WRONLY：只写
                O_RDWR：读写
                而且这三个是互斥的

                可选项：O_CREAT文件不存在，创建新文件
            - mode：八进制的数，表示用户对创建出的新的文件的操作权限，比如0777，0开头表示8进制数
            
            所谓0777
            rwx             rwx                     rwx
            当前用户的权限    当前用户所在组的权限      其他用户的权限
            如果都有就是
            111            111                     111  
            7               7                       7

            最终的权限是：(mode & ~umask)
            其中umask=002， ~umask=111111101=0775
            0777 -> 111111111
        &   0775 -> 111111101
        ---------------------
                    111111101=0775

            所以umask的作用是抹去某些权限，此处抹去了其他用户的写权限，如果是022就可以抹去用户组的写权限
            
            flags参数是一个int的数据，占4个字节，32位
*/



#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>      // perror()
#include <unistd.h>     // close()

int main()
{
    // 创建一个文件
    int fd = open("create.txt", O_RDWR | O_CREAT, 0777);
    if(fd == -1)
    {
        perror("open");
        return -1;
    }
    close(fd);
}