#include <stdio.h>
#include "myheader.h"

void f1A(void);
void f2A(void);

int main(void)
{
	union alpha a1;
	struct beta b1;
	printf ("Size of char = %d, short = %d, int = %d, long = %d\n", 
		(int)sizeof(char), (int)sizeof(short), (int)sizeof(int), (int)sizeof(long)); 
	printf ("Size of alpha is %d\n", (int)sizeof(union alpha));
	printf ("Size of beta is %d\n", (int)sizeof(struct beta));

	f1A();
	f2A();	
	return 0;
}
