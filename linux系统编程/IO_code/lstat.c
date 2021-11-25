#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    // 测试获取文件类型和权限
    struct stat st;
    stat(argv[1], &st);

    if( ( st.st_mode & S_IFMT ) == S_IFREG ){
        printf("this is relgure file");
    }
    else if( ( st.st_mode & S_IFDIR ) == S_IFDIR ){
        printf(" this is dir file ");
    }
    else if( (st.st_mode & S_IFLNK) == S_IFLNK ){
        printf("this is link file ");
    }

    return 0;

}