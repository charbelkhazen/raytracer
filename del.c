#include <stdio.h>


//std_assert should abort() , abort() sends a SIGABORT sig, -> ultimately I should have added kill() to implement asset, but not allowed
#include <stdlib.h>
#include <unistd.h>
void	std_assert(int cond)
{
	if (!cond)
	{
		exit(6);
	}
}
#include "signal.h"
#include "libft.h"
#define std_assert(expr) (expr ? (void)0 : std_assertfail(#expr))
static void std_assertfail(const char *expr)
{
	write(2, "Assertion Failure: ", 19); 
	write(2, expr, ft_strlen(expr));
	raise(SIGABRT);
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

//how to force arr size
int	std_itoa(char *arr, int n)
{
	int	integer_size;
	int	i;

	integer_size = getIntSize(n);
	std_assert(sizeof(arr) >= integer_size + 1);
	i = integer_size - 1;
	while (--i)
	{
		


		
	
}
#include <assert.h>
int main()
{
	std_assert(1==5);
}
