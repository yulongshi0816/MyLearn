#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
 
void my_func()
{
    int fd = open( "log.log", O_RDWR| O_CREAT| O_APPEND, 0755 );
    if( fd < 0 ){
        return;
    }
    // 获取当前系统时间
    time_t t;
    time( &t );

    // 转换时间
    char* p = ctime( &t );

    // 将时间写入

    write( fd, p , strlen(p) );
    close(fd );

    return;
}

int main()
{
    // 父进程fork子进程然后父进程退出
    pid_t pid = fork();

    if( pid < 0 || pid >0 ){
        exit(1);
    }

    // 子进程调用setid函数
    setsid();

    // 改变当前的工作目录
    chdir( "/home");

    // 改变文件掩码
    umask( 0022 );

    // 关闭文件描述符
    close( STDIN_FILENO );
    close( STDOUT_FILENO );
    close( STDERR_FILENO );

    // 执行核心操作
    // 注册信号处理函数
    struct sigaction act;
    act.sa_handler = my_func;
    act.sa_flags = 0;
    sigemptyset( &act.sa_mask );
    sigaction( SIGALRM, &act, NULL );

    // 设置时钟
    struct itimerval tm;
    tm.it_interval.tv_sec = 2;
    tm.it_interval.tv_usec = 0;
    // 第一次触发时间
    tm.it_value.tv_sec = 3;
    tm.it_value.tv_usec = 0;

    setitimer( ITIMER_REAL, &tm, NULL );

    printf( "afafaf" );

    while(1){
        sleep( 1 );
    }
    return 0;
}