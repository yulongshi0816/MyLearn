#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

typedef struct node{
    int data;
    struct node *next;
}NODE;

NODE *head = NULL;

pthread_mutex_t mutex;
pthread_cond_t cond;

void* producer( void* arg )
{
    NODE *pNode = NULL;
    while( 1 ){
        pNode = (NODE*) malloc( sizeof( NODE ) );
        if( pNode == NULL ){
            perror( "malloc error ");
            exit( -1 );
        }
        pNode->data = rand() % 1000;
        printf( "p:[%d]\n", pNode->data );
        // 加锁
        pthread_mutex_lock( &mutex );
        pNode->next = head;
        head = pNode;
        pthread_mutex_unlock( &mutex );
        pthread_cond_signal( &cond );
        sleep( rand() % 3 );
    }

}
// 线程处理函数
void* conusmer( void* arg )
{
    NODE *pNode = NULL;
    while( 1 ){
        pthread_mutex_lock( &mutex );
        if( head == NULL ){
            // 若条件不满足，则阻塞等待,并解锁
            // 若条件满足，被生产者通知，解除阻塞并加锁
            pthread_cond_wait( &cond, &mutex );
        }
        if( head == NULL ){
            pthread_mutex_unlock( &mutex );
            continue;
        }
        printf( "c:[%d]\n", head->data );
        pNode = head;
        head = head->next;
        pthread_mutex_unlock( &mutex );
        free( pNode );
        pNode = NULL;
        sleep( rand() % 3 );
    }
}

int main()
{
    pthread_mutex_init( &mutex, NULL );
    pthread_cond_init( &cond, NULL );
    pthread_t thread1;

    int ret = pthread_create( &thread1, NULL, producer, NULL );
    if( ret != 0 ){
        printf( "pthread create erro, [%s]\n", strerror( ret ) );
        return -1;
    }

    pthread_t thread2;

    ret = pthread_create( &thread2, NULL, conusmer, NULL );
    if( ret != 0 ){
        printf( "pthread create erro, [%s]\n", strerror( ret ) );
        return -1;
    }

    pthread_mutex_destroy( &mutex );
    pthread_cond_destroy( &cond );
    pthread_join( thread1, NULL );
    pthread_join( thread2, NULL );

    return 0;
}