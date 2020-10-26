#include <stdio.h>

int b = 100;
int fun()
{
	static int a = 100;
	return a++;
}


int main()
{
	static int a = 40;
	a = 0x10;
	printf("the a is %p\n", &a);
	printf("the is %p\n", main);
	return 0;
}
