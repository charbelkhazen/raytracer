#include <unistd.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h> //to del

void	std_assert(int cond)
{
	if (cond)
		return ;
	exit(134);
}

size_t	std_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

//only for p > 0
// attention int max !!! e.g. 10 ^ 16 ooverflowwww
int std_pow(int b, int p)
{
	if (!p)
		return (1);
	return	(b * std_pow(b, p - 1));
}

static int	getIntSize(int n)
{
	int	size;

	size = 1;
	while (n / 10)
	{
		size++;
		n/=10;
	}
	return (size);
}

int	std_sizeArray(int n)
{
	int	s;

	s = getIntSize(n);
	if (n < 0)
		++s;
	return (++s);
}

/*arr points at at least std_sizeArray(int number) bytes*/
void	std_itoa(char *arr, int n)
{
	int	start_i;
	int	end_i;

	start_i = 0;
	end_i = getIntSize(n);
	if (n < 0)
	{
		n *= -1;
		arr[start_i++] = '-';
		end_i++;
	}
	arr[end_i] = 0;
	while (end_i != start_i)
	{
		arr[--end_i] = '0' + n % 10;
		n /= 10;
	}
}

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

void	std_fillThenNull(char *arr, char c)
{
	*(arr++) = c;
	*arr = 0;
}

void	std_dtoa(char *arr, double n, int precision)
{
	int	whole;
	double	tmp;
	int	frac;
	
	whole = (int)n;
	//printf("whole is:%d\n", whole);
	std_itoa(arr, whole);
	//printf("arr on whole:%s\n", arr);
	std_fillThenNull(arr + std_strlen(arr), '.');
	//printf("arr after dot:%s\n", arr);
	tmp = (whole - n);
	//printf("extracted tmp:%f\n", tmp);
	if (tmp < 0)
		tmp  *= -1;
	frac = (int)(tmp * std_pow(10, precision));
	//printf("found frac:%d\n", frac);
	std_itoa(arr + std_strlen(arr), frac);
	//printf("arr end:%s\n", arr);
}

//needs assertion...refactor if time
int	std_strlcpy(char *dst, const char *src, int size)
{
	int	i;
	int	len;

	i = 0;
	len = std_strlen(src);
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

int	std_isWhiteSpace(char c)
{
	if (c == 32 ||  c == 9)
		return (1);
	return (0);
}

int	std_isNum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
