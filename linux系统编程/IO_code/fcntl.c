#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


int main( int argc, char* argv[])
{
    int fd = open( argv[1], O_RDWR );
    if( fd < 0 ){
        perror( "open error" );
        return -1;
    }

    // 调用fcntl复制文件描述符
    int newfd = fcntl( fd, F_DUPFD, 0);
    printf("fd: %d, newfd: %d \n", fd, newfd );

    // 修改文件描述符的flag属性
    // 使用fcntl获得fd的flag标识,并设置
    int flags = fcntl( fd, F_GETFL, 0 );
    flags |= O_APPEND;
    fcntl( fd, F_SETFL, flags );

    // 使用fd对文件写操作。
    write( fd, "hello world", sizeof("hello world") );
    // 移动文件指针到开始处
    lseek( fd, 0, SEEK_SET );

    //使用newfd读文件。
    char buf[64];
    memset( buf, 0, sizeof(buf) );
    int n = read( newfd, buf, sizeof(buf) );
    printf("read over: n=[%d], buf= [%s]\n", n, buf);

    close(fd);
    close(newfd);

    return 0;
}