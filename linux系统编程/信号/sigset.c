#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void sighandler( int signo )
{
    printf( " signo = [%d]\n", signo );
}

int main()
{
    signal( SIGINT, sighandler );
    // 定义信号集变量
    sigset_t set;

    // 初始化信号集
    sigemptyset( &set );

    // 将sigint和sigquit信号加入信号集中
    sigaddset( &set, SIGINT );
    sigaddset( &set, SIGQUIT );

    // 将信号加入到阻塞信号集中
    sigprocmask( SIG_BLOCK, &set, NULL );

    int i =0 , j = 1;
    sigset_t pending;
    while (1){
        // 获得未决信号集
        sigemptyset( &pending );
        sigpending( &pending );
        for( i = 1; i< 32; i++ ) {
            if (sigismember(&pending, i) == 1) {
                printf(" 1 ");
            } else {
                printf("0");
            }
        }
        printf(" \n ");
        j++;
        if( j % 10 == 0){
            sigprocmask( SIG_UNBLOCK, &pending, NULL );
        }
        else{
            sigprocmask( SIG_BLOCK, &pending, NULL );
        }
        sleep( 1 );
    }
    return 0;
}