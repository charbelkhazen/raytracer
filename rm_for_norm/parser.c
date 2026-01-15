//TODO:move and rename atod related function
//TODO:understand the post increment used in atod (or its helper function)
//TODO:complete ambient light parsing following the pseudocode written 

#include "stdlib.h"
#include "error.h"
#include <stdlib.h>

int	pars_consumeType(char **ptr_buf)
{
	char	*buf;
	int	type;

	std_assert(ptr_buf && *ptr_buf);

	buf = *ptr_buf;
	type = buf[0];

	if ((type == 's' && buf[1] == 'p') || (type == 'p' && buf[1] == 'l') || (type == 'c' && buf[1] == 'y'))
	    (*ptr_buf) += 2;
	else if (type == 'A' || type == 'C' || type == 'L')
	    (*ptr_buf) ++;
	else
	    return (0);
	pars_skipWhiteSpace(ptr_buf);
	return (type);
}


void	pars_skipWhiteSpace(char **ptr_buf)
{
	std_assert(ptr_buf && *ptr_buf);

	while (**ptr_buf && std_isWhiteSpace(**ptr_buf))
		(*ptr_buf) ++;
}

void	pars_raiseError(void)
{
	write(2, "Format Error .rt\n", 17);
	exit(1);
}

static char	*std_atodSignUtil(const char *s, double *sign)
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

static char	*std_atodNumberUtil(const char *s, double *res)
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
	char	*end;

	if (!buf || !out)
		return (0);

	end = std_atodSignUtil(buf, &sign);
	end = std_atodNumberUtil(end, &res);
	if (*end && !std_isWhiteSpace(*end) && *end != ',')
		return (0);

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

	while (**buf && (std_isNum(**buf) || **buf == '.'))
		(*buf)++;

	pars_skipWhiteSpace(buf);	
}

void	consume_Comma(char **buf)
{
	std_assert(buf && *buf); // may be useless

	if (**buf != ',')
		return (pars_raiseError());
	(*buf)++;
	pars_skipWhiteSpace(buf);	
}
	
void	pars_parseLight(char **buf)
{
	double	x;
	double	y;
	double	z;
	double	brightness;
	double	r;
	double	g;
	double	b;

	std_assert(buf && *buf);

	/* position x,y,z */
	pars_consumeNumber(&x, buf);
	consume_Comma(buf);
	pars_consumeNumber(&y, buf);
	consume_Comma(buf);
	pars_consumeNumber(&z, buf);

	/* mandatory whitespace before brightness */
	if (!std_isWhiteSpace(**buf))
		pars_raiseError();
	pars_skipWhiteSpace(buf);

	/* brightness */
	pars_consumeNumber(&brightness, buf);

	/* mandatory whitespace before color */
	if (!std_isWhiteSpace(**buf))
		pars_raiseError();
	pars_skipWhiteSpace(buf);

	/* color r,g,b (even if unused) */
	pars_consumeNumber(&r, buf);
	consume_Comma(buf);
	pars_consumeNumber(&g, buf);
	consume_Comma(buf);
	pars_consumeNumber(&b, buf);

	/* optional trailing whitespace */
	pars_skipWhiteSpace(buf);
}

int main()
{
	char	*str = "hello how are you";
}
