#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>


pthread_rwlock_t rwlock;

int num =0;
// 写线程
void* thread_write( void* arg )
{
    int n = *( int *) arg;
    int cur;
    while ( 1 ){
        pthread_rwlock_wrlock( &rwlock );
        cur = num;
        cur++;
        usleep( 500 );
        num = cur;
        printf( "[%d] -w:[%d]\n", n, cur );
        pthread_rwlock_unlock( & rwlock );
    }
}

void* thread_read( void* arg )
{
    int n = *( int *) arg;
    int cur;
    while( 1 ){
        pthread_rwlock_rdlock( &rwlock );
        cur = num;
        printf( "[%d] -R:[%d]\n", n, cur );
        pthread_rwlock_unlock( &rwlock );
        usleep( 400 );
    }
}

int main()
{
    int n = 8;
    int i ;
    pthread_t thread[n];
    pthread_rwlock_init( &rwlock, NULL );
    int arr[8];
    for( i=0; i< 3; i++){
        pthread_create( &thread[i], NULL, thread_write, &arr[i] );
    }

    for( i=3; i< 8; i++){
        pthread_create( &thread[i], NULL, thread_read, &arr[i] );
    }

    for( i=0; i < n; i++ ){
        pthread_join( thread[i], NULL );
    }

    pthread_rwlock_destroy( &rwlock );

    return 0;
}