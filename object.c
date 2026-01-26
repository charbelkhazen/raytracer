#include "object.h"

void	obj_fillObj(t_obj *obj, t_shape shape, t_mat mat, t_vec color)
{
	obj->shape = shape;
	obj->mat = mat;
	obj->color = color;
}

int	obj_hit(t_obj *obj, t_ray *ray, double t_min, double t_max, t_hitRec *rec)
{
	return (shape_hit(&obj->shape, ray, t_min, t_max, rec));
}
