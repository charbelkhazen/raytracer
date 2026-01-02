#include "stdlib.h"

int	std_sizeArrayDouble(double n, int precision)
{
	std_assert(precision > 1);
	return (std_sizeArray((int) n) + precision);
}

void	std_dtoa(char *arr, double n, int precision)
{
	int	whole;
	double	tmp;
	int	frac;
	int	size;
	
	whole = (int)n;
	std_itoa(arr, whole);
	tmp =  (whole - n);
	if (tmp < 0)
		tmp  *= -1;
	frac = (int)(tmp * std_pow(10, precision));
	std_itoa(arr + std_strlen(arr), frac);
}

int main()
{
	char	arr[100];

	std_dtoa(arr, 10.23, 1);
	printf("%s\n", arr);
}
