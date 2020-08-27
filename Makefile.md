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

### 4.1、Makefile基本要知道的东西

- 4.1.1显式规则概述

- 4.1.2隐晦规则概述

- 4.1.3变量的定义概述

- 4.1.4文件指示概述：

  1. 引用其他Makefile
  2. 指定Makefile中能编译不能编译的部分类似与#if
  3. 定义一个**多行命令**？？？？

- 4.1.5注释#

- 命令都用[Tab]开始

### 4.2、Makefile的文件名

### 4.3、引用其他Makefile

make在源make目录和其他目录下的找寻文件的顺序

make执行时加参数-I或--include-dir

make找不到文件和忽略无法读取文件的方法

### 4.4、环境变量MAKEFILES，尽量不用这个变量，会出现奇怪的事

### 4.5、Make的工作方式

多Makefile时执行的步骤：读入所有的Makefile->初始化变量->推导依赖关系，隐晦规则等->决定哪些目标要重新生成->执行生成命令

##   5、书写规则，make最终目标一般为第一个目标，伪目标也可

规则有两部分，依赖关系和生成目标的方法，明确Makefile最终目标，一般开始的第一个目标为最终目标

### 5.1、规则举例，类似于2.1，介绍最简单的规则

### 5.2、规则语法，多个文件间空格分号tab键的使用，换行符\的使用

### 5.3、通配符*?[...]~及通配符转义字符\

obj = *.o怎么理解，和obj := $(wildcard *.o)j区别

### 5.4、文件搜寻，让make在不同目录下寻找源文件.c，即VPATH变量的作用，vpath关键字的使用

### 5.5、伪目标.PHONY:clean/all/一口气编译多个目标的妙用

伪目标作为依赖，实现类似“子程序”的功能，伪目标本质是个标签，所以不会被生成，所以尽量用.PHONY指明

### 5.6、多目标：自动化变量$@的引出并简单举例

### 5.7、静态模式：$(objects): %.o: %.c 

### 5.8、自动生成依懒性[.d]文件，利用编译器找到C文件#include那些文件

## 6、书写命令

### 6.1、显示make执行的命令，使用@隐藏命令，-n只显示命令但不执行命令

### 6.2、命令执行，上一条命令结果应用于下一条命令时 ，需将这两条命令写在一行，用；隔开

### 6.3、命令出错的处理，使用-忽略，或其他方法终止

### 6.4、嵌套型Make，多级目录下的makefile使用，参数传递$(MAKE)

### 6.5、定义命令包，一次执行多个命令define

## 7、使用变量

Makefile中的变量和C语言中的宏区别在于其变量可以改变，变量的大小写规则，特殊字符规则

### 7.1、变量基础使用

### 7.2、变量中的变量， foo = $(bar),bar值可在任意地方，可前可后

### 7.2、:=，?=，=区别，使用#注释巧妙生成变量间的空格

### 7.3、变量的高级用法

#### 7.3.1、将变量中的指定字符串替换，%.c->%.o，.c=.o

#### 7.3.2、变量套变量$($(x))，变量套变量加函数使用（灵活使用变量）

### 7.4、追加变量值+=

### 7.5、override，命令行中的参数在Makefile中赋值

### 7.6、多行变量，define命令包，参考6.5

### 7.7、环境变量，make执行中默认使用的变量，若makefile中定义，则覆盖环境变量

### 7.8、目标变量，仅限于一个目标下使用的变量值prog : CFLAGS = -g

目标：变量 = / :=/ ?= 值

目标：依赖...

