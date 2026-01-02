#include "stdlib.h"
#include <stdio.h> // todel

int	std_sizeArrayDouble(double n, int precision)
{
	std_assert(precision > 1);
	return (std_sizeArray((int) n) + precision + 1);
}

void	std_dtoa(char *arr, double n, int precision)
{
	int	whole;
	double	tmp;
	int	frac;
	int	size;
	
	whole = (int)n;
	std_itoa(arr, whole);
	*(arr + std_strlen(arr)) = '.';
	tmp = (whole - n);
	if (tmp < 0)
		tmp  *= -1;
	frac = (int)(tmp * std_pow(10, precision));
	std_itoa(arr + std_strlen(arr), frac);
}

int main()
{
	char	arr[100];

	std_dtoa(arr, -10.23, 4);
	printf("whole thing:%s\n", arr);
}
