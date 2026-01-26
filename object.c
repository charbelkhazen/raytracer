#include "object.h"
#include "sphere.h"
#include <stdlib.h> //for exit() function

typedef struct s_hitRec t_hitRec;

void	obj_fillObj(t_obj *obj, t_shape shape, t_mat mat, t_vec color)
{
	obj->shape = shape;
	obj->mat = mat;
	obj->color = color;
}

int	obj_hit(t_obj *obj, t_ray *ray, double t_min, double t_max, t_hitRec *rec)
{
	if (obj->shape.type == SPHERE_TYPE)
		if(sph_hit(&obj->shape.as.sphere, ray, t_min, tmax, rec)) // can write it in one line with &&
			return (1);
	else
		exit(1); // shutdown everything, there should never be an object that is of unknown type (until now the sphere type is the only known one)
}
