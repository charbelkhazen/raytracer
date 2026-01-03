#include "stdlib.h"
#include <math.h>

int	std_cmpDouble(double a, double b, double eps)
{
	if (fabs(a - b) < eps)
		return (1);
	return (0);
}

int	std_sizeArrayDouble(double n, int precision)
{
	std_assert(precision > 0);
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
/*
int main()
{
	int	size = std_sizeArrayDouble(10.23, 1);
	printf("size:%d\n", size);
	char	arr[100];

	std_dtoa(arr, -10.23, 1);
	printf("whole thing:%s\n", arr);
}
*/
