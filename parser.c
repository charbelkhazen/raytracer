//TODO: shouldnt there be a range for x,y,z source coordinates
//TODO: + or - alone parse as 0 , consume Number issue??
//TODO: LIGHT PARSE SHOULD TAKE AS INPUT t_light and fill it , and no need for **buf as input , *buf works( we're working line by line)
//TODO: if lower case letter type -> more than once if upper just once-> SHOULD BE HANDLED BY PARSER
//TODO: SOME INFORMATION INSIDE ELEMTNS ARE NOT MANDATORY (E.G. COLOR FOR LIGHT) YET PARSER DOES CONSIDER THEM MANDATORY
//TODO: what if buffer (line) passed to pase light is just a line having a null termiinating byte ""
//TODO: need to explicitly skip white spaces when you can skip then (e.g. after parsing a single number) 


#include "stdlib.h"
#include "error.h"
#include <stdlib.h>
#include <unistd.h>
#include "vector.h"
#include "light.h"

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
	return (type);
}

/*
void	pars_raiseError(void)
{
	write(2, "Format Error .rt\n", 17);
	exit(1);
}
*/

int	pars_consumeNumber(double *num, char **buf)
{
	int	nbytes_consumed;

	std_assert(num && buf && *buf); //review this, maybe useless

	nbytes_consumed = 0;

	nbytes_consumed = std_atod(num, *buf);

	if (!nbytes_consumed)
		return (1);

	while (nbytes_consumed--)
		(*buf)++;

	return (0);
}

int	pars_consumeInteger(int *num, char **buf)
{
	int	nbytes_consumed;

	std_assert(num && buf && *buf); //review this, maybe useless

	nbytes_consumed = 0;

	nbytes_consumed = std_atoi(num, *buf);

	if (!nbytes_consumed)
		return (1);

	while (nbytes_consumed--)
		(*buf)++;

	return (0);
}

int	pars_consumeComma(char **buf)
{
	std_assert(buf && *buf); // may be useless

	if (**buf != ',')
		return (1);
	(*buf)++;

	return (0);
}

int	pars_consume3Numbers(t_vec *vector, char **buf)
{
	double	x;
	double	y;
	double	z;

	if (pars_consumeNumber(&x, buf))
		return (1);
	pars_skipWhiteSpace(buf);
	if (pars_consumeComma(buf))
		return (1);
	pars_skipWhiteSpace(buf);
	if (pars_consumeNumber(&y, buf))
		return (1);
	pars_skipWhiteSpace(buf);
	if (pars_consumeComma(buf))
		return (1);
	pars_skipWhiteSpace(buf);
	if (pars_consumeNumber(&z, buf))
		return (1);

	vec_fillVec(vector, x, y, z);

	return (0);
}

int	pars_consume3Integers(t_vec *vector, char **buf)
{
	int	x;
	int	y;
	int	z;

	if (pars_consumeInteger(&x, buf))
		return (1);
	pars_skipWhiteSpace(buf);
	if (pars_consumeComma(buf))
		return (1);
	pars_skipWhiteSpace(buf);
	if (pars_consumeInteger(&y, buf))
		return (1);
	pars_skipWhiteSpace(buf);
	if (pars_consumeComma(buf))
		return (1);
	pars_skipWhiteSpace(buf);
	if (pars_consumeInteger(&z, buf))
		return (1);

	vec_fillVec(vector, x, y, z);

	return (0);
}
int	pars_consumeMandatoryWhiteSpace(char **buf)
{
	if (!**buf || !std_isWhiteSpace(**buf))
		return (1);
	pars_skipWhiteSpace(buf);
	return (0);
}

int	pars_checkColorRange(t_vec color)
{
	double	x;
	double	y;
	double	z;

	x = color.x;
	y = color.y;
	z =  color.z;

	if (x < 0.0 || x > 255.0 || y < 0.0 || y > 255.0 || z < 0.0 || z > 255.0)
		return (1);
	return (0);
}

int	pars_checkUnitIntervalRange(double num)
{
	if (num < 0.0 || num > 1.0)
		return (1);
	return (0);
}

int	pars_parseLight(t_light *light, char *buf)
{
	std_assert(buf != 0);

	pars_skipWhiteSpace(&buf);
	if(pars_consume3Numbers(&light->src, &buf))
		return (1);
	if(pars_consumeMandatoryWhiteSpace(&buf))
		return (1);
	if(pars_consumeNumber(&light->bright, &buf))
		return (1);
	if(pars_checkUnitIntervalRange(light->bright))
		return (1);

	pars_skipWhiteSpace(&buf);

	if(*buf)
	{
		if(pars_consume3Integers(&light->color, &buf))
			return (1);
		if(pars_checkColorRange(light->color))
			return (1);
	}
	if (*buf)
		return (1);
	return (0);
}
