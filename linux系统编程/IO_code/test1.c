#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    int fd = open("./test.log", O_RDWR | O_CREAT, 0777);

    if( fd < 0 ){
        perror("open error");
        return -1;
    }
    // 写数据
    write( fd, "hello world", strlen("hello world") );
    // 移动文件指针到文件开始
    lseek( fd, 0, SEEK_SET );
    char buf[1024];
    memset( buf, 0, sizeof( buf) );
    int n = read( fd, buf, sizeof(buf) );
    printf("n= [%d], buf==[%s]\n", n, buf);
    // 关闭文件
    close(fd);

    return 0;

}