// 使用内存映射实现文件拷贝的功能
/*
    思路：
        1. 对原始的文件进行内存映射
        2. 创建一个新文件（扩展该文件）
        3. 把新文件的数据映射到内存中
        4. 通过内存拷贝将第一个文件的内存数据中拷贝到新的文件内存中
        4. 释放资源

*/

#include <unistd.h>
#include <stdio.h>  
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // 1. 对原始的文件进行内存映射
    int fd = open("test.txt", O_RDWR);
    if(fd == -1)
    {
        perror("open");
        exit(0);
    }
    int size = lseek(fd, 0, SEEK_END);  // 获取文件大小
    // 2. 创建一个新文件（扩展该文件）
    int fd1 = open("cpy.txt", O_RDWR|O_CREAT, 0777);
    if(fd1 == -1)
    {
        perror("open");
        exit(0);
    }

    // 对新创建的文件做拓展
    truncate("cpy.txt", size);
    write(fd1, "", 1);

    // 3. 分别做内存映射

    void * ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    void * ptr1 = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
    if(ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(0);
    }
    if(ptr1 == MAP_FAILED)
    {
        perror("mmap");
        exit(0);
    }
    // 内存拷贝
    memcpy(ptr1, ptr, size);

    munmap(ptr1, size);
    munmap(ptr, size);

    close(fd1);
    close(fd);

    return 0;
}
