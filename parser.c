//TODO: shouldnt there be a range for x,y,z source coordinates
//TODO: + or - alone parse as 0 , consume Number issue??
//TODO: if lower case letter type -> more than once if upper just once-> SHOULD BE HANDLED BY PARSER
//TODO: what if buffer (line) passed to pase light is just a line having a null termiinating byte ""
//TODO: err message here is the same for all types of issues. You can define errors in a very granular way by passing a str to every parsing function, and fill it on err. ONLY IF YOU HAVE TIME DO IT. Note: there are many other methods.
//TODO: review parse light and ambient to match the same structure of camera parsing. CHECK BEFORE WITH CHAT GPT IF HE THINKS ITS A GOOD IDEA
//TODO: m 'matte' M 'Metallic' make this explicit or fix to actually write matte and metallic IF THERE IS TIME ONLY
//TODO:  I let user write a sphere with diameter == 0 , remove it if needed by changing the checking condition to diameter <= 0 not < 0
//TODO: MAKE SURE CONSUME INTERGERS IS USED FOR COLORS (IN CAMERA - and double check all other parsers )!!!!!!!!!!!!!!!!!!!!
//TODO: PARSE MATERIAL IS COMPLETELY WRONG - ONLY WORKS FOR MATTE TYPE (FILLS ONLY WITH MATTE_TYPE"
//TODO: FORBIDDEN FUNCTION MEMSET!!!

#include <string.h> // FORBIDDEN FUNCTIONMEMESET - REMOVE LATER


#include "parser.h"
#include "stdlib.h"
#include "error.h"
#include <stdlib.h>
#include <unistd.h>
#include "vector.h"
#include "light.h"
#include "ambientlight.h"
#include "viewer.h"
#include "object.h"
#include "sphere.h"
#include "material.h"

void	pars_skipWhiteSpace(char **ptr_buf)
{
	std_assert(ptr_buf && *ptr_buf);

	while (**ptr_buf && std_isWhiteSpace(**ptr_buf))
		(*ptr_buf) ++;
}

//first letter alone does reveal the type
static int pars_associateTypeToLetter(t_cmd_type *type, int first_char)
{
	if (first_char == 'A')
		*type = AMBIENT_CMD;
	else if (first_char == 'L')
		*type = LIGHT_CMD;
	else if (first_char == 'C')
		*type = CAMERA_CMD;
	else if (first_char == 's' || first_char == 'c' || first_char == 'p')
		*type == OBJECT_CMD;
	else
		return (1); //NOTE: SHOULD NEVER HAPPEN.
	return (0);
}

int	pars_consumeType(t_cmd_type *type, char **ptr_buf)
{
	char	first_char;
	char	second_char;	

	std_assert(ptr_buf && *ptr_buf);

	first_char = **ptr_buf;

	//need to init second char anyways bcz of flags
	second_char = 0;
	if (first_char)
		second_char = *((*ptr_buf) + 1);

	if (( first_char == 's' && second_char == 'p') || (first_char == 'p' && second_char == 'l') || (first_char == 'c' && second_char == 'y'))
	    (*ptr_buf) += 2;
	else if (first_char == 'A' || first_char == 'C' || first_char == 'L')
	    (*ptr_buf) ++;
	else
	    return (1);

	//fill type
	if (pars_associateTypeToLetter(type, first_char))
		return (1);

	return (0);
}

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
//TODO : CONTAINS UNDERLYING ASSUMPTIONS THAT MAY CHANGE
// 1 - ASSUMES USER WRITES M or m for metallix and matte -> you can choose later to let user write the whole material type rather than first letter
// 2 - Assumes onlyu matte and Material
int	pars_consumeMaterial(material_type *mat_type, char **buf)
{
	std_assert(buf && *buf); // may be useless

	if (!(**buf == 'm' || **buf == 'M')) //matte or metallic - change later
		return (1);
	if (**buf == 'm')
		*mat_type = MATTE_TYPE;
	else if (**buf == 'M')
		*mat_type = METALLIC_TYPE;
	else
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

// fills material given that mat.type is filled by the corresponding type
// I assume all materials have  only a single element which is an int
// in matte, this single element is .onoff
// I choose to fill it with 0
static int pars_fillMaterial(t_mat *mat)
{
	if (mat.type == MATTE_TYPE)
		mat_fillMatte(mat, 0);
	//TODO:implement else if for all other materials
	else
		return (1); // should never fall here
	return (0);
}

//implementation using new obj struct
int	pars_parseSphere(t_obj *obj, char *buf)
{
	t_vec	center;
	t_vec	color;
	double	diameter;
	t_shape shape;
	t_mat	mat;

	std_assert(buf != 0);

	//default material is matte, if user inputs another then change (simulate default arg)
	mat.type = MATTE_TYPE;

	//parsing and consuming
	pars_skipWhiteSpace(&buf);
	// see those as ordered steps in parsing. and if a step fails -> returns (1) -> func returns (1). I wrote it in one line for compactness
	if (pars_consume3Numbers(&center, &buf) || pars_consumeMandatoryWhiteSpace(&buf) 
		|| pars_consumeNumber(&diameter, &buf) || pars_consumeMandatoryWhiteSpace(&buf)
		|| pars_consume3Integers(&color, &buf))
		return (1);
	pars_skipWhiteSpace(&buf);
	//optional material : 'm' : matte , 'M' : metallic 
	//see those as ordered sequence
	if(*buf)
	{
		if (pars_consumeMaterial(&mat.type, &buf)) 
			return (1);
		pars_skipWhiteSpace(&buf);
	}
	if(*buf)
		return (1);

	//check if consumed match logic
	if (pars_checkColorRange(color) || diameter < 0)
		return (1);

	//now I have validated : center, diameter, materialtype, color
	
	//we now fill
	shape_fillSphere(&shape, center, diameter / 2.0);
	//assumes material type has been added to mat
	pars_fillMaterial(&mat);
	return (0);
}

// line is either a command or empty
int	pars_parseLine(t_parsables *parsables, char *buf, t_cmd_type *cmdtype)
{
	int	cmd_type;

	pars_skipWhiteSpace(&buf);

	//empty line -> exit with no err
	if (!(*buf))
		return (0);

	if (!pars_consumeType(&cmd_type, &buf))
		return (1);
	
	if (cmd_type == 's')
		if (pars_parseSphere(&obj, &sphere, &material, buf))
			return (1);
	if (cmd_type == 'A')
		if (pars_parseAmbient(&ambient, buf))
			return (1);
	if (cmd_type == 'C')
		if (pars_parseCamera(&viewer, buf)) //NOT CAM
			return (1);
	if (cmd_type == 'L')
		if (pars_parseLight(&light, buf))
			return (1);
	else
		return (1);

	return (0);
}
