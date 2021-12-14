#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
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
        sleep(1);
    }
    else{

        printf( "this is child: %d\n", getpid() );
        execl( "/bin/ls", "ls", "-l", NULL );
        perror("execl error " );
    }
}