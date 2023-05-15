/*
    #include <pthread.h>

    int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
        - 功能：创建一个子线程
        - 参数：
            - thread：传出参数，线程创建成功后，子线程的线程ID被写道改                                                                                                                            变量中

*/
#include <stdio.h>
int main()
{
    short a = -1; unsigned short b = a; short c = a - b; int d = a- b;
printf("%x, %x\n",c, d);
    return 0;
}