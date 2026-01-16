//TODO:move and rename atod related function
//TODO: dtoa 's utils' return values are dirty (char *) ....
//TODO: shouldnt there be a range for x,y,z source coordinates


#include "stdlib.h"
#include "error.h"
#include <stdlib.h>
#include <unistd.h>
#include "vector.h"

void	pars_skipWhiteSpace(char **ptr_buf)
{
	std_assert(ptr_buf && *ptr_buf);

	while (**ptr_buf && std_isWhiteSpace(**ptr_buf))
		(*ptr_buf) ++;
}

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



void	pars_raiseError(void)
{
	write(2, "Format Error .rt\n", 17);
	exit(1);
}

void	std_atodSignUtil(char **buf, double *sign)
{
	*sign = 1.0;
	if (**buf == '-' || **buf == '+')
	{
		if (**buf == '-')
			*sign = -1.0;
		(*buf)++;
	}
}

void	std_atodNumberUtil(char **buf, double *res)
{
	double	frac;

	*res = 0.0;
	frac = 0.1;

	while (**buf >= '0' && **buf <= '9')
		*res = *res * 10.0 + (*(*buf)++ - '0');

	if (**buf == '.')
	{
		(*buf)++;
		while (**buf >= '0' && **buf <= '9')
		{
			*res += (*(*buf)++ - '0') * frac;
			frac *= 0.1;
		}
	}
}

int	std_atod(double *out, char *buf)
{
	double	sign;
	double	res;

	if (!buf || !out)
		return (0);

	std_atodSignUtil(&buf, &sign);
	std_atodNumberUtil(&buf, &res);

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

//SHOULD BE COMMA SEPERATED
static void	pars_consume3Numbers(t_vec *vector, char **buf)
{
	double	x;
	double	y;
	double	z;

	pars_consumeNumber(&x, buf);
	consume_Comma(buf);
	pars_consumeNumber(&y, buf);
	consume_Comma(buf);
	pars_consumeNumber(&z, buf);

	vec_fillVec(vector, x, y, z);
}

void	pars_consumeMandatoryWhiteSpace(char **buf)
{
	if (!std_isWhiteSpace(**buf))
		pars_raiseError();
	pars_skipWhiteSpace(buf);
}

void	pars_checkColorRange(t_vec color)
{
	double	x;
	double	y;
	double	z;

	x = color.x;
	y = color.y;
	z =  color.z;

	if (x < 0.0 || x > 255.0 || y < 0.0 || y > 255.0 || z < 0.0 || z > 255.0)
		return (pars_raiseError());
}

void	pars_checkUnitIntervalRange(double num)
{
	if (num < 0.0 || num > 255.0)
		return (pars_raiseError());
}

void	pars_parseLight(char **buf)
{
	t_vec	src;
	t_vec	color;
	double	brightness;

	std_assert(buf && *buf);

	pars_consume3Numbers(&src, buf);

	pars_consumeMandatoryWhiteSpace(buf);

	pars_consumeNumber(&brightness, buf);

	pars_checkUnitIntervalRange(brightness);

	pars_consumeMandatoryWhiteSpace(buf);

	pars_consume3Numbers(&color, buf);

	pars_checkColorRange(color);

	pars_skipWhiteSpace(buf);
}
/*
int main()
{
	char	*str = "hello how are you";
}
*/
