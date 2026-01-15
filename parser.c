#include "stdlib.h"
#include <stdlib.h>

int	pars_consumeType(char **ptr_buf)
{
	char	*buf;
	int	type;

	std_assert(ptr_buf && *ptr_buf);

	buf = *ptr_buf;
	type = buf[0];

	if ((type == 's' && buf[1] == 'p') || (type == 'p' && buf[1] == 'l') || (type == 'c' && buf[1] == 'y'))
	{
	    (*ptr_buf) += 2;
	    pars_skipWhiteSpace(ptr_buf);
	}
	else if (type == 'A' || type == 'C' || type == 'L')
	{
	    (*ptr_buf) ++
	    pars_skipWhiteSpace(ptr_buf);
	}
	else
	    return (0);
	return (type);
}


void	pars_skipWhiteSpace(char **ptr_buf)
{
	std_assert(ptr_buf && *ptr_buf);

	while (**ptr_buf && std_isWhiteSpace(**ptr_buf))
		(*ptr_buf) ++;
}

//at least len(str) = 17 
void	pars_errFormat(char *str) // can add more info, e.g. line
{
	char	*message;

	message = "format error .rt";
	std_strlcpy(str, &message, std_strlen(message));
	exit(1);
}

static const char	*parse_sign(const char *s, double *sign)
{
	*sign = 1.0;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			*sign = -1.0;
		s++;
	}
	return (s);
}

static const char	*parse_number(const char *s, double *res)
{
	double	frac;

	*res = 0.0;
	frac = 0.1;

	while (*s >= '0' && *s <= '9')
		*res = *res * 10.0 + (*s++ - '0'); //!!!!!!!!!!!!!!!!!!!!POST INCREMENT !!!!!!!!!!!!

	if (*s == '.')
	{
		s++;
		while (*s >= '0' && *s <= '9')
		{
			*res += (*s++ - '0') * frac;
			frac *= 0.1;
		}
	}
	return (s);
}

int	atod(const char *s, double *out)
{
	double	sign;
	double	res;

	if (!s || !out)
		return (0);

	s = parse_sign(s, &sign);
	parse_number(s, &res);
	*out = res * sign;
	return (1);
}

void	pars_consumeNumber(double *num, char **buff)
{
	if (!(std_isNum(**buf) || **buf == '-' || **buf == '+'))
		return (pars_errFormat()); 
	*num =  //atod ? pars_errFormat() : num transformed

	
	
void	pars_parseAmbient(char **buf)
{
		
	return ;
}

int main()
{
	char	*str = "hello how are you";
}
