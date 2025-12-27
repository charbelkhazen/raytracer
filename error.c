#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include "libft.h"

int	err_msgReturnOne(const char *msg)
{
	printf("Error: %s\n", msg);
	return (1);
}

void	err_writeStdErr(const char *msg, int n, ...)
{
	va_list	ap;

	va_start(ap, n);
	while (n)
	{
		if (write(2, msg, ft_strlen(msg)) == -1)
			return ;   // ENFORCE CONTRACT
		msg = va_arg(ap, const char *);
		n--;
	}
	va_end(ap);
}
