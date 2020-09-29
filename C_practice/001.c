#include <stdio.h>
 
int main(void)
{
    char *p = "hello world!\n";   //前面加const是规范写法，也可不加，但不加后面对“”内操作不会报错，但也是无法修改的
   const char buf[] = {"hello world\n"};
    const char *b;
    b = buf;
    *b = 'a';   //会报错，因为指定const就不允许修改
    //b[2] = 'n'; 
    printf("%s", b);
}