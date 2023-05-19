/*
    互斥量的类型pthread_mutex_t

    int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
        - 初始化互斥量
        - 参数：
            - mutex：互斥量变量
            - attr：互斥量属性，一般使用默认值 NULL
        - restrict：c语言修饰符，被修饰的指针不能由另外的指针操作

    int pthread_mutex_destroy(pthread_mutex_t *mutex);
        - 释放互斥量的资源

    int pthread_mutex_lock(pthread_mutex_t *mutex);
        - 加锁，阻塞的，如果一个线程加锁了，其他线程只能阻塞等待

    int pthread_mutex_trylock(pthread_mutex_t *mutex);
        - 尝试加锁，加锁失败不会阻塞，直接返回

    int pthread_mutex_unlock(pthread_mutex_t *mutex);
        - 解锁
*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
//#define __USE_MISC 1
#include <unistd.h>

#define ThreadNum 3

void * sellTickets(void * arg);

// 创建一个互斥量，全局区，不能在main，因为main执行完了局部变量就没了
pthread_mutex_t mutex;

int main()
{
    // 初始化互斥量
    pthread_mutex_init(&mutex, NULL);

    // 创建三个子线程
    pthread_t tid[ThreadNum];
    for(int i = 0; i < ThreadNum; i++)
    {
        int ret = pthread_create(&tid[i], NULL, sellTickets, NULL);
        if(ret != 0)
        {
            char * error = strerror(ret );
            printf("error: %s\n", error); 
        }
    }

    // 回收子线程资源
    for (int i = 0; i < ThreadNum; i++)
    {
        pthread_join(tid[i], NULL);
    }

    pthread_exit(NULL); // 退出主线程

    // 释放互斥量
    pthread_mutex_destroy(&mutex);   
    return 0;
}

void * sellTickets(void * arg)
{

    // 买票
    static int tickets = 1000;
    
    while(1)
    {
        // 加锁
        pthread_mutex_lock(&mutex);
        if(tickets>0)
        {
        usleep(500000);
        printf("%ld 正在卖第 %d 张门票\n", pthread_self(), tickets);
        tickets--;

        }
        else
        {
            pthread_mutex_unlock(&mutex);

            break;
        }

        // 解锁 
        pthread_mutex_unlock(&mutex);
    }
    return NULL; 
}