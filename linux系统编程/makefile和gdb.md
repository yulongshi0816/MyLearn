## makefile
### makefile的基本规则
makefile由一组规则组成，规则如下：\
  目标：依赖\
 （tab）命令\
makefile基本三要素：
- 目标： 要生成的的目标文件
- 依赖：目标文件由那些文件生成。
- 命令：通过执行该命令由依赖文件生成目标。

第一个版本\
```makefile
main: main.c fun1.c fun2.c sum.c
    gcc -o main main.c fun1.c fun2.c sum.c
```

### makefile工作原理
检查规则:\
    要想生成目标文件，要先检查依赖文件是否都存在：\
    若都存在，则比较目标时间和依赖时间，如果依赖的时间比目标的时间新，则重新生成目标，否则不重新生成\
    若不存在，则往下找有没有生成依赖的规则，有就生成\
第二个版本
```makefile
main: main.o fun1.o fun2.o sum.o
    gcc -o main main.o fun1.o fun2.o sum.o
main.o: main.c
    gcc -c main.c -I./
fun1.o: fun1.c
    gcc -c fun1.c
sum.o: sum.c
    gcc -c sum.c
```
### makefile 中的变量
makefile在中使用变量有点类似于c中的宏定义，使用该变量相当于内容替换，使用该变量可以使makefile易于维护。
#### 普通变量
var = hello,$(var)
第三个版本
```makefile
target=main
objects=main.o fun1.o fun2.o sum.o
CC=gcc
CPPFLAGS=-I/
$(target): $(objects)
    $(CC) -o $@ $(objects)
main.o: main.c
    $(CC) -c ¥< $(CPPFLAGS)
fun1.o: fun1.c
    $(CC) -c $<
sum.o: sum.c
    $(CC) -c $<
```
#### 自动变量
只能在规则当中的命令使用
$@:规则中的目标\
$<: 表示规则中的第一个条件。\
$^:表示规则中的所有条件，组成一个列表以空格隔开
#### 模式规则
第四个版本
```makefile
target=main
objects=main.o fun1.o fun2.o sum.o
CC=gcc
CPPFLAGS=-I/
$(target): $(objects)
    $(CC) -o $@ $(objects)
%.o : %c
    $(CC) -C $< $(CPPFLAGS)
```
### makefile函数
wildcard- 查找指定目录下指定类型的文件\
    src=$(wildcard *.c) // 找到当前目录下所有后缀为.c的文件，复制给src\
patsubst- 匹配替换 \
obj=$(patsubst %.c, %,o, $(src)) // 把所有变量里后缀为.c的文件替换为.o\
第五个版本
```makefile
target=main
src=$(wildcard *.c)
objects=$(patsubst %.c, %.o, $(src))
CC=gcc
CPPFLAGS=-I/
$(target): $(objects)
    $(CC) -o $@ $(objects)
%.o : %c
    $(CC) -C $< $(CPPFLAGS)
```
### makefile的清理操作
.PHONY 定义为伪目标，无论如何都执行\
第五个版本
```makefile
target=main
src=$(wildcard *.c)
objects=$(patsubst %.c, %.o, $(src))
CC=gcc
CPPFLAGS=-I/
$(target): $(objects)
    $(CC) -o $@ $(objects)
%.o : %c
    $(CC) -C $< $(CPPFLAGS)

.PHONY clean
clean:
    rm -rf $(objects) $(main)
```
使用-f可以指定makefile文件，如make -f makefffff

## gdb调试
gdb调试是在程序运行结果与预期不符合的时候可以使用gdb进行调试，特别注意：使用gdb调试的时候需要加上-g
### 启动
gdb program\
执行程序：\
    run: 遇到断点则停，否则执行到结尾。\
    start: 执行到第一条语句\
list:
- list file: 显示file的代码
- list file:fun: 显示file的fun函数
- list： 显示当前行后面的代码
- list linenume：查看当前文件linenum
- set listsize n: 设置list显示行数
### 设置断点
break：
- b 10: 当前文件设置第10行断点。
- b fun: 在fun函数舍则断点
- i b: 查看断点信息
- b file:fun1: 在file文件的fun1出设置断点。
- disable 断点号：设置该断点无效
- enable 断点号: 设置断点好有效
- d 断点号：删除断点
- b 9 if i == 9: 设置第9行条件断点
### 代码调试
step：单步调试，进入函数体或者循环体。\
finish：退出进入的函数。\
until: 退出循环体\
continue：继续运行程序，可以简写为c（若有断点，则直接跳到下一断点处。）\
print: 打印变量。\




























































































