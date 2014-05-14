#include <stdio.h>
#include <stdlib.h>
#include "event.h"

int main()
{
	u_char a;
	char b;

	a = 0xff;
	b = 0x81;

	printf("a:%d\nb:%d\n", a, b);
	return 0;
}
