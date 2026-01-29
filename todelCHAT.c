Here is the modified parser implementation ( I only show some of its functions not all) ( I show only snippets of the implementaion)

//first letter alone does reveal the type
static int pars_associateTypeToLetter(t_cmd_type *type, int first_char)
{
	if (first_char == 'A')
		*type = AMBIENT_CMD;
	else if (first_char == 'L')
		*type = LIGHT_CMD;
	else if (first_char == 'C')
		*type = CAMERA_CMD;
	else if (first_char == 's')
		*type = SPHERE_CMD;
	//TODO: else if for plane and cylinder!!!
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

//TODO : CONTAINS UNDERLYING ASSUMPTIONS THAT MAY CHANGE
// 1 - ASSUMES USER WRITES M or m for metallix and matte -> you can choose later to let user write the whole material type rather than first letter
// 2 - Assumes onlyu matte and Material
int	pars_consumeMaterial(material_type *mat_type, char **buf)
{
	std_assert(buf && *buf); // may be useless

	if (!(**buf == 'm')) //TODO: ADD || **buf == 'M' , 'P' for plastic etc..
		return (1);
	if (**buf == 'm')
		*mat_type = MATTE_TYPE;
	else
		return (1);

	//else if (**buf == 'M')
	//*mat_type = METALLIC_TYPE;  //TODO: add mettalic and other textures 

	(*buf)++;
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

//fills an OBJECT not a sphere
//returns 1 on err
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
	obj_fillObj(obj, shape, mat, color);
	return (0);
}

// line is either a command or empty
int	pars_parseLine(t_parsables *parsables, char *buf, t_cmd_type *cmdtype)
{
	pars_skipWhiteSpace(&buf);

	//empty line -> exit with no err
	if (!(*buf))
		return (0);

	if (pars_consumeType(cmd_type, &buf))
		return (1);
	
	if (*cmd_type == SPHERE_CMD)
		if (pars_parseSphere(&parsables->obj, buf))
			return (1);
	else if (*cmd_type == AMBIENT_CMD)
		if (pars_parseAmbient(&parsables->ambient, buf))
			return (1);
	else if (*cmd_type == CAMERA_CMD)
		if (pars_parseCamera(&parsables->view, buf)) //NOT CAM
			return (1);
	else if (*cmd_type == LIGHT_CMD)
		if (pars_parseLight(&parsables->light, buf))
			return (1);
	else
		return (1);
	//TODO: missing plane and cyl
	return (0);
}

here are some dependables:
- parser interface snippet:

typedef struct s_parsables
{
	t_light light;
	t_amb	amb;
	t_view	view;
	t_obj	obj;
}	t_parsables;

typedef enum
{
	CAMERA_CMD;
	LIGHT_CMD;
	AMBIENT_CMD;
	SPHERE_CMD;
	CYLINDER_CMD;
	PLANE_CMD; //NOTE: cyl and plane already implemented here
}	t_cmd_type;

void	pars_skipWhiteSpace(char **ptr_buf);

//STRICT CONTRACT: PTR_BUF MUST BE NUL TERMINATED
//type is case sensitive : 'c' : cylinder != 'C' : camera
//assumes no whitespace, consumes and advances the type
int	pars_consumeType(int *type, char **ptr_buf);

//assumes no whitespaces. Consume number and advances. double parsing relies on atod, returns 1 on err
int	pars_consumeNumber(double *num, char **buf);

//assumes no whitespaces. Consume int and advances. int parsing relies on atoi, returns 1 on err
int	pars_consumeInteger(int *num, char **buf);

//No whitespace assumptoin. consume comma. If no comma return (1) (parsin err)
int	pars_consumeComma(char **buf);

//assumes comma seperation between them, allows for whitespace between numbers
int	pars_consume3Numbers(t_vec *vector, char **buf);

int	pars_consume3Integers(t_vec *vector, char **buf);

int	pars_consumeMandatoryWhiteSpace(char **buf);

int	pars_checkColorRange(t_vec color);

int	pars_checkUnitIntervalRange(double num);

int	pars_parseLight(t_light *light, char *buf);

int	pars_parseAmbient(t_ambientLight *ambient, char *buf);

int	pars_parseCamera(t_viewer *view, char *buf);

int	pars_parseSphere(t_obj *obj, t_sph *sphere, t_mat *material, char *buf);

here is a snippet of object interface 

typedef struct s_obj
{
	t_shape		shape;
	t_mat		mat;
	t_vec		color;
}	t_obj;

here is a snippet of shape interface 

typedef enum
{
	SPHERE_TYPE
	//CYLINDER_TYPE;
	//PLANE_TYPE;
}	shape_type;

typedef struct s_shape
{
	shape_type	type;
	union
	{
		t_sph sphere;
		//t_cyl cylinder;
		//t_pl plane;
	} as;
}	t_shape;

here is a snippet of material interface 

typedef enum
{
	MATTE_TYPE
	//METALLIC_TYPE;
	//GLASS_TYPE;
}	material_type;


typedef struct s_material
{
	material_type type;
	union
	{
		t_matte matte;
		//t_met metallic;
		//t_gl  glass;
	} as;
}	t_mat;

here is a snippet of sphere interface

typedef struct s_sphere
{
	int	obj_type;
	t_vec   center;
	double  radius;
}	t_sph;

