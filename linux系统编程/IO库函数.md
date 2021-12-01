## IO库函数
### 阻塞与非阻塞
read函数在读完文件内容后，若再次read，则read函数会立刻返回，表明read函数读普通文件是非阻塞的。\
设备文件/dev/tty\
通过读终端设备文件，表示read读设备文件是阻塞的。\
阻塞和非阻塞非read函数的属性，而是文件本身的属性。\
socket和pipe文件这两种文件都是阻塞的。\

### 文件操作相关函数
#### lstat/stat
获取文件属性\
int stat(const char* pathname, struct stat *buf);\
int stat(const char* pathname, struct stat *buf);\
函数返回值:\
- 成功返回0
- 失败返回-1

           struct stat {
               dev_t     st_dev;     /* ID of device containing file */
               ino_t     st_ino;     /* inode number */
               mode_t    st_mode;    /* protection */
               nlink_t   st_nlink;   /* number of hard links */
               uid_t     st_uid;     /* user ID of owner */
               gid_t     st_gid;     /* group ID of owner */
               dev_t     st_rdev;    /* device ID (if special file) */
               off_t     st_size;    /* total size, in bytes */
               blksize_t st_blksize; /* blocksize for file system I/O */
               blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
               time_t    st_atime;   /* time of last access */
               time_t    st_mtime;   /* time of last modification */
               time_t    st_ctime;   /* time of last status change */
           };
使用st_mode成员判断文件类型和权限。\
lstat和stat：
- 对于普通文件而言，二者一样。
- 对于软连接来说，lstat函数获取的是连接文件本身属性，stat获取的是链接文件指向的文件属性。
### 目录操作相关函数
dup函数：复制文件描述符\
newfd = dup( oldfd );\
返回最小且没有被占用的文件描述符。当调用dup函数之后，newfd和oldfd都指向了同一文件，内核会在内部维护一个计数，此时计数为2，当close一个文件描述符之后，这个计数为1，只有当计数为0时候才能真正关闭。\
通过fd对文件进行写操作，使用newfd对文件进行读操作，若读到，则认为fd和newfd指向相同文件。\
dup2函数：复制文件描述符\
int dup2( int oldfd, int newfd );\
如果newfd已经指向了文件，会先将newfd所指向的文件关闭，再指向oldfd的文件。\


  




































