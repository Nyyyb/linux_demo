/*

    读写锁的类型pthread_rwlock_t

    int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr);

    int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);

    int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);

    int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);

    int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);

    int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);

    int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);

    案例：8个线程操作同一个全局变量 
    3个线程不定时的写这个全局变量
    5个线程不定时的读这个全局变量
*/

#include <stdio.h>
//#define __USE_UNIX98 1
#include <pthread.h>
//#define __USE_MISC 1
#include <unistd.h>

#define WriteThreadNum 3
#define ReadThreadNum 5

// 创建一个共享数据
int num = 1;
pthread_mutex_t mutex;
pthread_rwlock_t rwlock;


void * writeFunc(void * arg);
void * readFunc(void * arg);

int main()
{
//    pthread_mutex_init(&mutex, NULL);
    pthread_rwlock_init(&rwlock, NULL);
    // 创建三个写线程
    pthread_t wtids[WriteThreadNum], rtids[ReadThreadNum];

    for (int i = 0; i < WriteThreadNum; i++)
    {
        pthread_create(&wtids[i], NULL, writeFunc, NULL);
    }

    // 设置线程分离
    for (int i = 0; i < WriteThreadNum; i++)
    {
        pthread_detach(wtids[i]);
    }

    // 创建五个读线程
    for (int i = 0; i < ReadThreadNum; i++)
    {
        pthread_create(&rtids[i], NULL, readFunc, NULL);
    }
    
    // 设置线程分离
    for (int i = 0; i < WriteThreadNum; i++)
    {
        pthread_detach(rtids[i]);
    }
    
    pthread_exit(NULL);
//    pthread_mutex_destroy(&mutex);
    pthread_rwlock_destroy(&rwlock);
    return 0;

}

void * writeFunc(void * arg)
{
    while (1)
    {
        pthread_rwlock_wrlock(&rwlock);
        num++;
        printf("++write, tid : %ld, num : %d\n", pthread_self(), num);
        pthread_rwlock_unlock(&rwlock);
        usleep(100);

    }
    
    return NULL;
}

void * readFunc(void * arg)
{
    while (1)
    {
        pthread_rwlock_rdlock(&rwlock);
        printf("===read, tid : %ld, num : %d\n", pthread_self(), num);
        pthread_rwlock_unlock(&rwlock);
        usleep(100);
    }
    
    return NULL;   
}