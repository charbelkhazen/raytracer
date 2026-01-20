//TODO: shouldnt there be a range for x,y,z source coordinates
//TODO: + or - alone parse as 0 , consume Number issue??
//TODO: if lower case letter type -> more than once if upper just once-> SHOULD BE HANDLED BY PARSER
//TODO: what if buffer (line) passed to pase light is just a line having a null termiinating byte ""
//TODO: err message here is the same for all types of issues. You can define errors in a very granular way by passing a str to every parsing function, and fill it on err. ONLY IF YOU HAVE TIME DO IT. Note: there are many other methods.
//TODO: review parse light and ambient to match the same structure of camera parsing. CHECK BEFORE WITH CHAT GPT IF HE THINKS ITS A GOOD IDEA
//TODO: m 'matte' M 'Metallic' make this explicit or fix to actually write matte and metallic IF THERE IS TIME ONLY
#include "stdlib.h"
#include "error.h"
#include <stdlib.h>
#include <unistd.h>
#include "vector.h"
#include "light.h"
#include "ambientlight.h"
#include "viewer.h"

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

int	pars_consumeMaterial(int *mat, char **buf)
{
	std_assert(buf && *buf); // may be useless

	if (!(**buf == 'm' || **buf == 'M'))
		return (1);

	*mat = (**buf);
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
//could have used fill light
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

//could have used fillAmbient 
int	pars_parseAmbient(t_ambientLight *ambient, char *buf)
{
	std_assert(buf != 0);

	pars_skipWhiteSpace(&buf);

	if(pars_consumeNumber(&ambient->ratio, &buf))
		return (1);
	if(pars_checkUnitIntervalRange(ambient->ratio))
		return (1);

	if(pars_consumeMandatoryWhiteSpace(&buf))
		return (1);

	if(pars_consume3Integers(&ambient->color, &buf))
		return (1);
	if(pars_checkColorRange(ambient->color))
		return (1);

	pars_skipWhiteSpace(&buf);

	if (*buf)
		return (1);

	return (0);
}

int	pars_parseCamera(t_viewer *view, char *buf)
{
	t_vec	lookfrom;
	t_vec	orientation_vector;
	double	hfov; 

	std_assert(buf != 0);

	//parsing and consuming
	pars_skipWhiteSpace(&buf);
	// see those as ordered steps in parsing. and if a step fails -> returns (1) -> func returns (1). I wrote it in one line for compactness
	if (pars_consume3Numbers(&lookfrom, &buf) || pars_consumeMandatoryWhiteSpace(&buf) 
		|| pars_consume3Numbers(&orientation_vector, &buf) || pars_consumeMandatoryWhiteSpace(&buf)
		|| pars_consumeNumber(&hfov, &buf))
		return (1);
	pars_skipWhiteSpace(&buf);
	if (*buf)
		return (1);

	//check if consumed match logic
	if (!std_cmpDoubles(vec_vectorLen(&orientation_vector), 1)
		|| (hfov < 0 || hfov > 180.0))
		return (1);
	
	viewer_defaultFill(view, lookfrom, hfov, orientation_vector);
	return (0);
}

int	pars_parseSphere(t_obj *obj, char *buf)
{
	t_vec	center;
	t_vec	color;
	double	diameter;
	int	mat;

	std_assert(buf != 0);

	//default material is matte, if user inputs another then change (simulate default arg)
	mat = 'm';

	//parsing and consuming
	pars_skipWhiteSpace(&buf);
	// see those as ordered steps in parsing. and if a step fails -> returns (1) -> func returns (1). I wrote it in one line for compactness
	if (pars_consume3Numbers(&center, &buf) || pars_consumeMandatoryWhiteSpace(&buf) 
		|| pars_consumeNumber(&diameter, &buf) || pars_consumeMandatoryWhiteSpace(&buf)
		|| pars_consume3Numbers(&color, &buf))
		return (1);
	pars_skipWhiteSpace(&buf);
	//optional material : 'm' : matte , 'M' : metallic 
	//see those as ordered sequence
	if(*buf) || (pars_consumeMaterial(&material, &buf) || (*buf))
		return (1);

	//check if consumed match logic : only colors should be cheched
	if (pars_checkColorRange(color))
		return (1);
	viewer_defaultFill(view, lookfrom, hfov, orientation_vector);
	return (0);
}
