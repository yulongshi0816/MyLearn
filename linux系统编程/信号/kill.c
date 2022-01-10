#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void sighandler( int signo )
{
    printf( "signo=[%d]\n", signo );
}

int main()
{

    // 注册信号处理函数
    signal( SIGALRM, sighandler );

    struct itimerval tm;
    // 周期性时间赋值
    tm.it_interval.tv_sec = 1;
    tm.it_interval.tv_usec = 0; // 必须赋值，否则会是一个随机值
    // 第一次触发的时间
    tm.it_value.tv_sec = 3;
    tm.it_value.tv_usec = 0;
    setitimer( ITIMER_REAL, &tm, NULL );

    while ( 1 ){
        sleep( 1 );
    }
    return 0;
}