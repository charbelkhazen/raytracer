//TODO:move and rename atod related function
//TODO:understand the post increment used in atod (or its helper function)
//TODO:complete ambient light parsing following the pseudocode written 

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

void	pars_raiseError(void) // can add more info, e.g. line
{
	char	*message;

	message = "format error .rt";
	std_strlcpy(str, &message, std_strlen(message));
	exit(1);
}

static const char	*std_atodSignUtil(const char *s, double *sign)
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

static const char	*std_atodNumberUtil(const char *s, double *res)
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

int	std_atod(double *out, char *buf)
{
	double	sign;
	double	res;

	if (!buf || !out)
		return (0);

	buf = std_atodSignUtil(buf, &sign);
	std_atodNumberUtil(buf, &res);
	*out = res * sign;
	return (1);
}

void	pars_consumeNumber(double *num, char **buf)
{
	std_assert(num && buf && *buf); //review this, maybe useless

	if (!(std_isNum(**buf) || **buf == '-' || **buf == '+'))
		return (pars_raiseError()); 
	if (!std_atod(num, *buf))
		return (pars_raiseError());
	pars_skipWhiteSpace(buf);	
}

void	consume_Comma(char **buf)
{
	std_assert(buf && *buf); // may be useless

	if (**buf != ',')
		return (pars_raiseError());
	(*buf)++;
}
	
void	pars_parseAmbient(char **buf)
{
	//consume number 
	//consume white space 
	//consume comma
	//consume number 
	//consume white space 
	//consume comma
	//consume number 
	//consume white space  //MANDATORY (check if)

	//consume number

	//mandatory white space
	//number
	//whitespace
	//comma
...
	return ;
}

int main()
{
	char	*str = "hello how are you";
}
