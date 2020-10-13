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

#### char buf[] = "abc"与以上带buf[10]的区别
带10数组固定分配10个值，不带编译器自动为数组分配值数量等于“abc”需要数量，此处为4个

### 初始化完后二次赋值
#### 分为字符空间和非字符空间拷贝
- 字符空间：使用ascii码来解码的空间-->给人看的空间，\0作为结束标志
- 非字符空间：解析成具体的数值
二者定义的时候养成习惯：
char buf[10];-->string
unsigned char buf[10];-->data

#### 字符空间拷贝原则
一块空间，当成字符空间时，C语言提供了一套字符拷贝函数
字符拷贝函数的原则：内存空间间的逐一赋值，一旦出现0，函数就即将结束

#### strcpy()
最基本的字符拷贝函数，使用时注意内存泄露问题，此函数看到0才结束

#### 非字符空间拷贝原则
三个：
src： source源地址
dest：destination目的地址
num：number拷贝个数

#### memcpy()
```c
void *memcpy(void *dest, const void *src, size_t n);//字符拷贝函数，以下是使用范例

int buf[10];
int sensor[100];
memcpy(buf, sensor, 10*sizeof(int));//n表示byte,故需要计算字节数目
//此处不使用strcpy或strnpy是因为这两个都会识别0为字符串结束标志，所以拷贝会出问题


```
### 指针数组char *a[100]
本质是数组里面存放了指针
int a[100]--->int 修饰a里面的每个值的类型a[0],a[1]...
char *a [100]--->char 修饰a[0],a[1]...里存放的指针指向内容的属性，即指向char类型的值对应地址
以上两个a，sizeof(a) = 100 * 4 

#### 指针数组和二维指针的关系 char **a
本质上是一样的，都是指向指针的指针
char **a 是一个指向指针的指针
char *a[100]是100个指向指针的指针

### 数组名和指针的关系
