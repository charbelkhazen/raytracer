#include <unistd.h>
#include <signal.h>


#define std_assert(expr) (expr ? (void)0 : std_assertfail(#expr)) // subtle -> macro because permits dealing with expr as int and str

size_t	std_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void std_assertfail(const char *expr)
{
	write(2, "Assertion Failure: ", 19); 
	write(2, expr, std_strlen(expr)); //does not respect no io condition
	raise(SIGABRT);//change to exit before eval and remove header
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
int	std_itoa(char *arr, int n)
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
	return (0);
}

static int std_extract_frac(double n)
{
	int	whole;
	double	frac;

	if (n < 0)
		n *= -1;
	frac = n - (int)n;
	whole = (int) (frac * 16);
	while (!(whole % 10))
		whole /= 10;	
	return (whole);
}

int	std_dtoa(char *arr, double n)
{
	double	frac;
	int	int_frac;
	int	integer;			

	integer = (int)n;
	std_itoa(arr, integer);
	frac = (integer - n);
	if (frac < 0)
		frac *= -1;
	return (0); // FIX FIX FIX
}

#include <stdio.h>
int main()
{
	printf("%d\n", std_extract_frac(12.45));
}
