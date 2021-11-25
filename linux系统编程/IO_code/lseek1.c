#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// 实现文件的扩展
int main(int argc, char* argv[]){
    int fd = open( argv[1], O_RDWR);

    if( fd < 0 ){
        perror("open error");
        return -1;
    }
    // 异地哦那个文件指针到100哥字节处
    lseek( fd, 100, SEEK_END );
    // 进行一次写入操作
    write( fd, "H", 1 );
    // 关闭文件
    close(fd);

    return 0;

}