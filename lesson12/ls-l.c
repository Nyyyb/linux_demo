#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

#include <pwd.h>
#include <grp.h>

#include <time.h>

#include <string.h>

// -rw-rw-r-- 1 nyyyb nyyyb   12 4月  20 14:23 a.txt
int main(int argc, char *argv[])
{
    // printf("%d\n", argc);
    struct stat statbuf;
    if (argc < 2)
    {
        printf("%s filename\n", argv[0]);
        return -1;
    }

    int ret = stat(argv[1], &statbuf);
    if (ret == -1)
    {
        perror("stat");
        return -1;
    }

    char perms[11] = {0}; // 保存文件类型和权限

    // 判断文件类型
    switch (statbuf.st_mode & __S_IFMT)
    {
    case __S_IFSOCK:
        perms[0] = 's';
        break;
    case __S_IFLNK:
        perms[0] = 'l';
        break;
    case __S_IFREG:
        perms[0] = '-';
        break;
    case __S_IFBLK:
        perms[0] = 'b';
        break;
    case __S_IFDIR:
        perms[0] = 'd';
        break;
    case __S_IFCHR:
        perms[0] = 'c';
        break;
    case __S_IFIFO:
        perms[0] = 'p';
        break;

    default:
        perms[0] = '?';
        break;
    }
    // 判断文件的访问权限
    // 判断文件所有者

    perms[1] = (statbuf.st_mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (statbuf.st_mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (statbuf.st_mode & S_IXUSR) ? 'x' : '-';
    perms[4] = (statbuf.st_mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (statbuf.st_mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (statbuf.st_mode & S_IXGRP) ? 'x' : '-';
    perms[7] = (statbuf.st_mode & S_IROTH) ? 'r' : '-';
    perms[8] = (statbuf.st_mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (statbuf.st_mode & S_IXOTH) ? 'x' : '-';
    perms[10] = '\0';
    // if (statbuf.st_mode & S_IRUSR)
    // {
    //     printf("r");
    // }
    // else
    // {
    //     printf("-");
    // }
    printf("%s ", perms);

    printf("%ld ", statbuf.st_nlink);

    char *fileUser = getpwuid(statbuf.st_uid)->pw_name;
    printf("%s ", fileUser);

    char *fileGrp = getgrgid(statbuf.st_gid)->gr_name;
    printf("%s ", fileGrp);

    printf("%ld ", statbuf.st_size);

    char *mtime = ctime(&statbuf.st_mtime);
    char time[512] = {0};
    strncpy(time, mtime, strlen(mtime) - 1);

    printf("%s ", time);
    printf("%s\n", argv[1]);

    char buf[1024];
    sprintf(buf, "%s %ld %s %s %ld %s %s", perms, statbuf.st_nlink, fileUser, fileGrp, statbuf.st_size, time, argv[1]);
    printf("%s\n", buf);
    return 0;
}
