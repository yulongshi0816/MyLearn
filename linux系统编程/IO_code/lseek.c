#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    int fd = open( argv[1], O_RDWR);

    if( fd < 0 ){
        perror("open error");
        return -1;
    }
    // 调用lseek获取文件大小
    int len = lseek( fd, 0, SEEK_END );
    printf("file len: %d", len );
    // 关闭文件
    close(fd);

    return 0;

}