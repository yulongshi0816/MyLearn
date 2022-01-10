#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

// 循环创建子线程并且打印是第几个子线程

struct test{
    int data;
    char name[64];
};
// 线程处理函数
void* mythread( void* arg )
{
    int i = *(int *)arg;
    if( i == 3 ){
        pthread_exit( NULL );
    }
    printf( "n == [%d] ", i );
//    printf( "child,thread, id= [%ld]\n", pthread_self() );
}

int main()
{
    pthread_t thread[5];
    int a[5] = { 0, 1, 2, 3, 4};
    int ret;
    for( int i = 0; i< 5; i++){
        ret = pthread_create( &thread[i], NULL, mythread, &a[i] );
        if( ret != 0 ){
            printf( "pthread create erro, [%s]\n", strerror( ret ) );
            return -1;
        }
    }

    sleep( 1 );

    return 0;
}

// 为什么一开始都是5
// 由于i的内存只有一块，这块内存被五个子线程共享，主线程在一个cpu时间片内完成了5个子线程的创建，此时i的值为5，而其他的子线程在主线程让
// 出cpu时间片之后才能执行，因此每个子线程读到的内存值都是5。