# C语言内存

## 指针基础

### 指针修饰符
#### const    常量，只读，不能变

- const char *p = char const *p,

    p is a pointer to const char

    p可任意指向，但指向的内容不允许修改，类似于字符串“hello world!”

- char * const p = char *p const

    const p is a pointer to char

    p指向的位置固定，内容可变，一般为硬件资源，寄存器地址等

- const char * const p

    const p is a pointer to const char

    指向内容和位置都不许变,一般为ROM设备

## 数组

原理：另外一种对内存的操作方式，本质上跟指针是一样的

- int a[100]

a是个常量标签，不是指针，出现a = xxx时是错误的，a++也错（相当于a+=1）
### 初始化
#### int a[10] = 空间 
#### C语言{}的意义
- **C语言默认使用{}来表示空间，即看到{}要想到一整块的空间操作**
- int a[10] = {10,20,30}	//此步骤只是方便程序员操作，实际执行相当于逐一依次赋值,程序执行效率不变

#### char buf[10] = {'a','b','c'}	普通数组用法
此处涉及到字符串和数组，一定注意
- **字符串和数组重要区别：尾部有一个'\0'**

#### char buf[10] = {"abc"}	字符串用法
- “”作用是自动在abc末尾加上‘\0'

#### char buf[10] = "abc"
是上一种{"abc"}写法的简化版，等效

#### char buf[10] = "abc"与char *p = "abc"区别
- char *p = "abc"
原理：指针p指向了“abc”对应的地址
- char buf[10] = "abc"
原理：将“abc”的值依次赋值给buf[0],buf[1],buf[2]...而"abc"另外存在了与buf不同的位置
因此：若出若出现以下情况
p[2] = 'e'	错误，p指向的是const常量"abc"
buf[2] = 'e'	正确，buf就是个普通数组，可随意变