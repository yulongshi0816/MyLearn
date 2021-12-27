#include <stdio.h>
#include <stdlib.h
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void sighandler( int signo )
{
    printf("signo=[%d]", signo );
}

int main()
{
    // 创建管道
    int fd[2];
    int ret = pipe( fd );
    if ( ret < 0 ){
        perror( "pip error " );
        return -1;
    }
    // 注册信号处理函数
    signal( SIGPIPE, sighandler );
    // 关闭读端
    close( fd[0] );
    write( fd[1], "hello world", strlen("hello world"));
    return 0;
}
