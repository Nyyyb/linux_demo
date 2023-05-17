/*
    #include <pthread.h>

    int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
        - 功能：创建一个子线程
        - 参数：
            - thread：传出参数，线程创建成功后，子线程的线程ID被写道改    
            - attr: 设置线程的属性，一般使用默认值 NULL
            - start_routine: 函数指针，这个函数是子线程需要处理的逻辑代码
            - arg：给第三个参数使用的，传参
        返回值：
            成功：0
            失败：错误码，和errno不一样
            获取错误号信息：char * strerror(int errnum);

*/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void * thread_start(void * arg)
{
    printf("子线程开始执行，参数为：%d\n", *(int *)arg);
    return NULL;
}

int main()
{
    pthread_t tid;
    // 创建一个子线程
    int num = 10;
    int ret = pthread_create(&tid, NULL, thread_start, (void *)&num);
    if(ret != 0)
    {
        char * error = strerror(ret);
        printf("error: %s\n", error);
    }
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", i);
    }
    sleep(1);
    
    return 0;
}