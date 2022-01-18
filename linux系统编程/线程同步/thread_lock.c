#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define NUM 5000

int number = 0;
// 线程处理函数
void* mythread( void* arg )
{
    int n;
    for ( int i= 0; i<NUM; i++ ) {
        n = number;
        n++;
        number = n;
    }
    //printf( "child,thread, id= [%ld]\n", pthread_self() );
}

int main()
{
    pthread_t thread1;

    int ret = pthread_create( &thread1, NULL, mythread, NULL );
    if( ret != 0 ){
        printf( "pthread create erro, [%s]\n", strerror( ret ) );
        return -1;
    }

    pthread_t thread2;

    ret = pthread_create( &thread2, NULL, mythread, NULL );
    if( ret != 0 ){
        printf( "pthread create erro, [%s]\n", strerror( ret ) );
        return -1;
    }

    printf("number == [%d]", number );
    pthread_join( thread1, NULL );
    pthread_join( thread2, NULL );

    return 0;
}