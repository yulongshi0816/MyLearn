#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <semaphore.h>

typedef struct node{
    int data;
    struct node *next;
}NODE;

NODE *head = NULL;

sem_t sem_producer;
sem_t sem_comuser;

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
        sem_wait( &sem_producer );
        pNode->next = head;
        head = pNode;
        sem_post( &sem_comuser );
        sleep( rand() % 3 );
    }

}
// 线程处理函数
void* conusmer( void* arg )
{
    NODE *pNode = NULL;
    while( 1 ){
        sem_wait( &sem_comuser );
        printf( "c:[%d]\n", head->data );
        pNode = head;
        head = head->next;
        sem_post( &sem_producer );
        free( pNode );
        pNode = NULL;
        sleep( rand() % 3 );
    }
}

int main()
{
    sem_init( &sem_producer, 0, 5 );
    sem_init( &sem_comuser, 0, 0 );
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

    pthread_join( thread1, NULL );
    pthread_join( thread2, NULL );

    sem_destory( &sem_comuser );
    sem_destory( &sem_producer );

    return 0;
}