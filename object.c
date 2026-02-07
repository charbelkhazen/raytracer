#include "object.h"
#include "interval.h"

void	obj_fillObj(t_obj *obj, t_shape shape, t_mat mat, t_vec color)
{
	obj->shape = shape;
	obj->mat = mat;
	obj->color = color;
}

int	obj_hit(t_obj *obj, t_ray *ray, t_interval *time_interval, t_hitRec *rec)
{
	double t_min = time_interval->min;
	double t_max = time_interval->max;
	return (shape_hit(&obj->shape, ray, t_min, t_max, rec));
}
