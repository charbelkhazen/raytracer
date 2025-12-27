#include <stdio.h>
#include <unistd.h>

char	*foo(int n)
{
	char	digit;

	if (n / 10)
		foo(n / 10);
	digit = '0' + n % 10;
	write(1, &digit, 1);
}

char	*
char	*itoa(double n)
{
	double fractional;
	int	n_precision;

	n_precision = 16;
	fractional = ((int)n) - n;
	if (fractional < 0)
		fractional *= -1;
	while (n_precision)
	{
		fractional *= 10;
		n_precision --;
	}
	while (!(fractional % 10))
		fractional /= 10;
	
}

int main()
{
	printf("%zu\n", sizeof(double));	
}
