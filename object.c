#include "object.h"

void	obj_fillObj(t_obj *obj, t_shape shape, t_mat mat, t_vec color)
{
	obj->shape = shape;
	obj->mat = mat;
	obj->color = color;
}
