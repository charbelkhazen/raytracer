#include "stdlib.h" 
#include <stdio.h>

int std_pow(int b, int p)
{
	int res;

	if (!p)
		return (1);
	return	b * std_pow(b, p - 1);
}
