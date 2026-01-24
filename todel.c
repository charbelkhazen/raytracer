Here are some code I rely upon:

t_obj interface :

typedef struct s_obj
{
	t_shape		shape;
	t_mat		mat;
	t_vec		color;
}	t_obj;

void	obj_fillObj(t_obj *obj, t_shape shape, t_mat mat, t_vec color);

sphere implementation:

typedef struct s_sphere
{
	int	obj_type;
	t_vec   center;
	double  radius;
}	t_sph;

void	sph_fillSph(t_sph *sphere, t_vec center, double radius);

//returns bool AND if hit fills hitRec
int	sph_hit(t_sph *sphere, t_ray *ray, double t_min, double t_max, t_hitRec *rec);

and here is my implementation of parse sphere :
//implementation using new obj struct
int	pars_parseSphere(t_obj *obj, char *buf)
{
	t_vec	center;
	t_vec	color;
	double	diameter;
	int	mat_type;

	std_assert(buf != 0);

	//default material is matte, if user inputs another then change (simulate default arg)
	mat_type = MATTE_TYPE;

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
		if (pars_consumeMaterial(&mat_type, &buf)) 
			return (1);
		pars_skipWhiteSpace(&buf);
	}
	if(*buf)
		return (1);

	//check if consumed match logic
	if (pars_checkColorRange(color) || diameter < 0)
		return (1);

	//now I have validated : center, diameter, mat_type, color
	
	//we now fill
	obj->shape.type = SPHERE_TYPE;
	sph_fillSph(&(obj->shape.as.sphere), center, diameter / 2.0);
	obj->mat.type = mat_type; // FIX LATER
	//I do not fill material because until now the specific material struct (matte) has no elements
	obj->color = color;
	return (0);
}




Is the implementation of parse sphere correct 
PLEASE FOCUS ON WHAT IS AFTER THE 
//now I have validated : center, diameter, mat_type, color
comment
