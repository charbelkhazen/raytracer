#include <math.h>
int	std_cmpDouble(double a, double b, double eps)
{
	if (fabs(a - b) < eps)
		return (1);
	return (0);
}

#include <stdlib.h> // itoa

void dtoa_1dec(double x, char *out)
{
    int ip = (int)x;                 // integer part
    int fp = (int)((x - ip) * 10);    // first decimal digit

    char buf[16];
    itoa(ip, buf, 10);

    char *p = out;
    for (int i = 0; buf[i]; i++) *p++ = buf[i];
    *p++ = '.';
    *p++ = '0' + (fp < 0 ? -fp : fp);
    *p = '\0';
}

#include "stdlib.h"



#include <stdio.h>
int main()
{
	printf("%d\n", std_cmpDouble(0.1 + 0.2, 0.3, 1e-9));
}
