#include "object.h"
#include "vector.h"
#include "shape.h"
#include "material.h"

//need to add material after
void	obj_fillObj(t_obj *obj, t_shape shape, t_mat mat, t_vec color)
{
	obj->shape = shape;
	obj->mat = mat;
	obj->color = color;
}
