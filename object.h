#include "vector.h"
#include "material.h"
#include "shape.h"

typedef struct s_obj
{
	t_shape		shape;
	t_material	material;
	t_vec		color;
}	t_obj;

//need to add material after
void	obj_fillObj(t_obj *obj, t_shape shape, t_material mat, t_vec color);
