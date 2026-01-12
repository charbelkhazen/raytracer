#include "object.h"

void	obj_fillObj(t_obj *obj, int obj_shapeType, void *obj_shape, int obj_matType, void *obj_mat)
{
	obj->obj_shapeType = obj_shapeType;
	obj->obj_shape = obj_shape;
	obj->obj_matType = obj_matType;
	obj->obj_mat = obj_mat;
}
