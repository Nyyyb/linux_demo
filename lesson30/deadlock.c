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
        usleep(5000);
        printf("%ld 正在卖第 %d 张门票\n", pthread_self(), tickets);
        tickets--;

        }
        else
        {
            pthread_mutex_unlock(&mutex);

            break;
        }

        // 解锁 
        // pthread_mutex_unlock(&mutex);
    }
    return NULL; 
}