# 参考《跟我一起写Makefile.pdf》正点原子linux资料百度云里有
实际本文大致为此文档的目录作用，主要还是参考此文档

## 软件使用

使用sourceCRT控制linux终端

使用ftp实现文件互传

## .c -> .exe过程(*参第二部分*)

预处理：把.h .c展开成一个文件（宏定义直接替换，头文件，库文件一块形成.i文件）

​									gcc -E hello.c -o hello.i

汇编：.i 生成一个汇编代码文件 .s

​									gcc -S hello.i -o hello.S

编译: .s 生成一个.o （.obj文件,即Object File）

​									gcc -c hello.S -o hello.o

链接：将所有的.o文件链接为一个.exe 文件（Windows里）.elf（linux里）

​									gcc hello.o -o hello

## Makefile规则（常识，参2.1）

显式规则如下，隐晦规则make自动推导功能引起（写一个简单命令执行一堆默认规则）
```makefile
target ... : prerequisites ...

command 
#显式规则写的明明白白，一眼能看懂，不过隐晦规则能大幅缩小篇幅，看起来巨简单
```
- target ：目标文件，可为.o文件，可执行文件，标签（Label）
- prerequisites：生成target所需文件，依赖文件
- command：命令（任意shell命令）
- makefile放在最前面的目标为make默认目标

## make工作原理（参2.3）

根据目标文件是否比后面的依赖文件修改时间新决定，如果目标最新，则不执行下面命令，然后判断后面的依赖文件的依赖文件，层层递推，一直到.c,.h,.S文件的新旧，即，**若有一个.c被改变，则此条线上跟这个.c有关的都会执行一遍，无关的不变**

## makefile的变量（参2.4）

Makefile变量本质：使用一个字符串代表另一个比较繁琐的字符串

objects = main.o kbd.o command.o display.o \
insert.o search.o files.o utils.o

使用时：

edit : $(objects)**等效于**edit : main.o kbd.o command.o display.o \
insert.o search.o files.o utils.o

## makefile自动推导（参2.5）

make看到一个[.o]文件，会自动把[.c]文件加在依赖关系中，例如，找到一个whatever.o，自动默认whatever.c为其依赖文件，并且能推导出cc -c whatever.c命令，于是**以下两段代码等效**：

```makefile
objects = main.o kbd.o command.o display.o \
insert.o search.o files.o utils.o
edit : $(objects)
cc -o edit $(objects)
main.o : main.c defs.h
cc -c main.c
kbd.o : kbd.c defs.h command.h
cc -c kbd.c
command.o : command.c defs.h command.h
cc -c command.c
display.o : display.c defs.h buffer.h
cc -c display.c
insert.o : insert.c defs.h buffer.h
cc -c insert.c
search.o : search.c defs.h buffer.h
cc -c search.c
files.o : files.c defs.h buffer.h command.h
cc -c files.c
utils.o : utils.c defs.h
cc -c utils.c
#####等效于以下
objects = main.o kbd.o command.o display.o \
insert.o search.o files.o utils.o
edit : $(objects)
cc -o edit $(objects)
main.o : defs.h
kbd.o : defs.h command.h
command.o : defs.h command.h
display.o : defs.h buffer.h
insert.o : defs.h buffer.h
search.o : defs.h buffer.h
files.o : defs.h buffer.h command.h
utils.o : defs.h
```

## clean

clean永远放在最后面，如果放在最前面，则clean成为make的默认目标

最稳健的clean如下：

```makefile
...
.PHONY : clean
clean :
-rm edit $(objects)
```

## 4.1、Makefile基本要知道的东西

- 4.1.1显式规则概述

- 4.1.2隐晦规则概述

- 4.1.3变量的定义概述

- 4.1.4文件指示概述：

  1. 引用其他Makefile
  2. 指定Makefile中能编译不能编译的部分类似与#if
  3. 定义一个**多行命令**？？？？

- 注释

  
