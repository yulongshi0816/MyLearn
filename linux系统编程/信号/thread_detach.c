#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

// 线程处理函数
void* mythread( void* arg )
{
    printf( "child,thread, id= [%ld]\n", pthread_self() );
}

int main()
{
    pthread_t thread;
    int ret = pthread_create( &thread, NULL, mythread, NULL );
    if( ret != 0 ){
        printf( "pthread create erro, [%s]\n", strerror( ret ) );
        return -1;
    }

    // 设置线程分离属性
    pthread_detach( thread );

    ret = pthread_join( thread , NULL );

    if ( ret !=0 ){
        printf("pthread_join  error [%s]\n", strerror( ret ));
    }
    sleep( 1 );

    return 0;
}