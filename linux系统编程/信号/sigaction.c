#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
// 完成信号的注册

void sighandler( int signo )
{
    printf( " signo = [%d]\n", signo );
}

int main()
{
    // 注册sigint信号处理函数
    struct sigaction sig;

    sig.sa_handler = sighandler;
    sigemptyset( &sig.sa_mask ); // 阻塞的信号
    sigaddset( &sig.sa_mask, SIGQUIT );
    sig.sa_flags = 0;

    sigaction( SIGINT, &sig, NULL );
    while( 1 ){
        sleep( 1 );
    }

    return 0;
}