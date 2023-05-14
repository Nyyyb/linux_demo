/*
    #include <sys/mman.h>

    void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
        - 功能：
            映射一个文件中的数据到内存中
        - 参数：
            - void *addr: 映射的起始地址，一般设置为NULL，让系统自动分配
            - size_t length: 要映射的数据的长度，建议使用文件的长度
                获取文件的长度：stat lseek
                分页
            - int prot: 映射区域的保护方式，对映射区的操作权限
                PROT_EXEC  Pages may be executed.
                PROT_READ  Pages may be read.
                PROT_WRITE Pages may be written.
                PROT_NONE  Pages may not be accessed. 没有权限
                按位或
                要操作映射内存，必须要有读的权限
                PROT_READ | PROT_WRITE
            - int flags: 影响映射区域的各种特性
                MAP_SHARED 与其它所有映射这个对象的进程共享映射空间，进程间通信，必须设置这个选项
                MAP_PRIVATE 建立一个写入时拷贝（类似fork的写时复制，读时共享）的私有映射空间
                            不同步，内存映射区的数据改变了，对原来的文件不影响
            - int fd: 要映射的文件的文件描述符
                - open得到，open的是一个磁盘文件
                - 文件的大小不能为0，open指定的权限不能与prot冲突
                    prot: PROT_READ | PROT_WRITE -> open: O_RDWR
                    prot: PROT_READ -> open: O_RDONLY或O_RDWR
            - offset: 偏移量，一般不用，必须是4k的整数倍
        返回值：
            - 成功：返回映射区的首地址
            - 失败：返回MAP_FAILED
                errno
    int munmap(void *addr, size_t length);
        - 功能：释放内存映射
        - 参数：
            - void *addr: 要释放的起始地址
            - size_t length: 映射区域的长度，与mmap中的length一样

*/

/*
    使用内存映射实现进程间通信：
    1. 有关系的进程（父子）
        - 还没有子进程的时候
            - 通过唯一的父进程，先创建内存映射区
        - 有了内存映射区后，创建子进程
        - 父子进程可以共享创建的内存映射区了

    2. 没有关系的ipc
        - 准备一个大小不是0的磁盘文件
        - 进程1通过磁盘文件创建内存映射区
            - 得到一个操作这块内存的指针
        - 进程2通过磁盘创建内存映射区
            - 得到一个操作这块内存的指针
        - 使用内存映射区通信
    
    注意：内存映射区是非阻塞的
*/

#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

int main()
{

    // 1. 打开一个文件
    int fd = open("test.txt", O_RDWR);
    if(fd == -1)
    {
        perror("open");
        exit(0);
    }
    
    int size = lseek(fd, 0, SEEK_END);  // 获取文件大小

    // 2. 创建内存映射区
    int* ptr= mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(0);
    }

    // 3. 创建子进程
    pid_t pid = fork();
    if(pid>0)
    {
        // 父进程
        strcpy((char*)ptr, "nihao a , son!!!");
    }
    else if(pid == 0)
    {
        // 子进程
        char buf[64];
        strcpy(buf, (char*)ptr);
        printf("read data : %s\n", buf);
    }
    munmap(ptr, size);
    close(fd);

    return 0;   
}

// 使用内存映射区实现没有关系的进程通信