#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main( int argc, char* argv[] )
{
    pid_t pid = fork();
    if( pid < 0 ){
        perror("process creat error");
        return -1;
    }
    else if( pid > 0 ){
        printf( "this is father: %d\n", getpid() );
        int status;
        pid_t wid = waitpid( -1, &status, WNOHANG ); // -1 表示等待任意子进程
        printf( "wpid = [%d]", wid );

    }
    else{

        printf( "this is child: %d\n", getpid() );
        execl( "/bin/ls", "ls", "-l", NULL );
        perror("execl error " );
    }
}