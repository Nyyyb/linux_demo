/*
    #include <unistd.h>

    ssize_t read(int fd, void *buf, size_t count);
        参数：
            - fd：文件描述符，通过open()函数返回的，通过文件描述符操作某个文件
            - buf：需要读取数据存放的地方，数组的地址
            - count：要读取的字节数，指定的数组的大小
        返回值：
            - 成功：返回读取的字节数
                >0：读取的字节数
                =0：读到文件末尾
            - 失败：返回-1，并且设置errno

    #include <unistd.h>

    ssize_t write(int fd, const void *buf, size_t count);
        参数：
            - fd：文件描述符
            - buf：要写入的数据的地址
            - count：要写入的字节数
        返回值：
            - 成功：返回写入的字节数
            - 失败：返回-1，并且设置errno
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    // char *buf[20] = {0};
    // int fd = open("src.txt", O_RDONLY, 0777);
    // if (fd == -1)
    // {
    //     perror("open");
    //     return -1;
    // }
    // ssize_t rtv = read(fd, buf, 20);
    // if (rtv == -1)
    // {
    //     perror("read");
    //     return -1;
    // }
    // else
    //     printf("%d bytes have been read\n", (int)rtv);

    // close(fd);
    // fd = open("dst.txt", O_RDWR | O_CREAT, 0777);
    // if (fd == -1)
    // {
    //     perror("open");
    //     return -1;
    // }
    // rtv = write(fd, buf, 20);
    // if (rtv == -1)
    // {
    //     perror("write");
    //     return -1;
    // }
    // else
    // {
    //     printf("%d bytes have been written\n", (int)rtv);
    // }
    // close(fd);
    int srcfd = open("src.txt", O_RDONLY, 0777);
    if (srcfd == -1)
    {
        perror("open");
        return -1;
    }

    int dstfd = open("dst.txt", O_WRONLY | O_CREAT, 0777);
    if (dstfd == -1)
    {
        perror("open");
        return -1;
    }
    char * buf[3] = {0};
    int len = 0;
    while((len = read(srcfd, buf, sizeof(buf)))>0)
    {
        write(dstfd, buf, len);
    }

    close(dstfd);
    close(srcfd);

}