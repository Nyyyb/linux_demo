/*
    int pthread_attr_init(pthread_attr_t *attr);
        - 初始化线程属性变量
    int pthread_attr_destroy(pthread_attr_t *attr);
        - 释放线程的属性资源
    int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
        - 获取线程分离的状态属性
    int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
        - 设置线程分离的状态属性
*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>

void * start_routine(void * arg)
{
    printf("child thread id: %lu\n", pthread_self());
    for (int i = 0; i < 10; i++)
    {
        printf("child : %d\n", i);
    }
    return NULL;
}   

int main()
{
    // 创建一个线程属性变量
    pthread_attr_t attr;
    // 初始化属性变量
    pthread_attr_init(&attr);
    // 设置属性
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    // 获取线程的栈的大小
    size_t stacksize;
    // 创建一个线程
    pthread_t tid;

    int ret = pthread_create(&tid, &attr, start_routine, NULL);
    if(ret != 0)
    {
        char * error = strerror(ret);
        printf("error: %s\n", error);
    }

    pthread_attr_getstacksize(&attr, &stacksize);
    printf("thread stack size : %ld\n", stacksize);
    // 输出主线程和子线程的id
    printf("tid : %ld\nmain thread id : %ld\n", tid, pthread_self());

    

    // 设置分离后，对分离的子线程进行连接pthread_join()
    ret = pthread_join(tid, NULL);
    if(ret != 0)
    {
        char * error = strerror(ret);
        printf("error1: %s\n", error);
    }

    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", i);
    }
    // 释放线程属性资源
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
    
    return 0;
}