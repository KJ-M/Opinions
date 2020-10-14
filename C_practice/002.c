#include <stdio.h>
typedef struct
{
    char a;
    int b;
} str;
int b;
int main()
{
    int a;
    printf("a:%p \n", &a);
    printf("main:%p \n", main);
    printf("b:%p \n", &b);

    return 0;
}