/*
    打开一个目录
    #include <sys/types.h>
    #include <dirent.h>

    DIR *opendir(const char *name);
        参数：
            - name：要打开的目录的名称
        返回值：
            DIR *类型：理解为目录流信息，结构体指针
            错误返回NULL，errno


    读取目录中的数据
    #include <dirent.h>

    struct dirent *readdir(DIR *dirp);
        参数：dirp是opendir返回的结果
        返回值：
            - struct dirent *：代表读取到的文件信息
            读取到末尾或者失败了，返回NULL

    关闭目录
    #include <sys/types.h>
    #include <dirent.h>

    int closedir(DIR *dirp);
*/
// #define __USE_MISC
#define _DEFAULT_SOURCE

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>


// 读取某个目录下所有的普通文件的个数

// 格式：./a.out lesson15



int main(int argc, char *argv[])
{
    // 打开一个目录
    if (argc < 2)
    {
        printf("./%s dirname", argv[0]);
        return -1;
    }

    return 0;
}

// 用于获取目录下所有普通文件的个数
int getFileNum(const char *path)
{
    static count = 0;
    // 打开目录
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        perror("opendir error");
        return -1;
    }
    struct dirent *ptr;
    while ((ptr = readdir(dir)) != NULL)
    {
        char *dname = ptr->d_name;
        if (strcmp(dname, "..") == 0 || strcmp(dname, ".") == 0)
        {
            continue;
        }
        if(ptr->d_type == DT_DIR)
        {
            char * newpath = 
            // 目录
        }
        if(ptr->d_type == DT_REG)
        {
            // 普通文件
        }
    }
}