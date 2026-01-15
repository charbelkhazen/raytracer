#include "stdlib.h"

int	pars_consumeType(char **ptr_buf)
{
	char	*buf;
	int	type;

	std_assert(ptr_buf && *ptr_buf);

	buf = *ptr_buf;
	type = buf[0];
	if (type != 'A' && type != 'C' && type != 'L')
	{
		if (!(type == 's' && buf[1] == 'p') && !(type == 'p' && buf[1] == 'l') && !(type == 'c' && buf[1] = 'y'))
			return (0);
		else
			(*ptr_buf) ++;
	}
	else
		(*ptr_buf) ++;
	
	return (type);
}

void	pars_skipWhiteSpace(char **ptr_buf)
{
	char	*buf;

	buf = *ptr_buf;

	while (*buf == 32 || ( *buf >= 9 && *buf <= 13)
		(*ptr_buf) ++;
}
