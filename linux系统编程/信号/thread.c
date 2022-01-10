#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

struct test{
    int data;
    char name[64];
};
// 线程处理函数
void* mythread( void* arg )
{
    struct test *p = ( struct test *)arg;
    printf( "n == [%d],name==[%s] ", p->data, p->name );
    printf( "child,thread, id= [%ld]\n", pthread_self() );
}

int main()
{
    pthread_t thread;
    struct test t;

    memset( &t, 0, sizeof(t) );
    t.data = 88;
    strcpy( t.name, "小文");
    int n = 99;
    int ret = pthread_create( &thread, NULL, mythread, &t );
    if( ret != 0 ){
        printf( "pthread create erro, [%s]\n", strerror( ret ) );
        return -1;
    }

    sleep( 1 );

    return 0;
}