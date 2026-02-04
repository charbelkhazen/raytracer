#include "intersection.h"

void	lp_shade(t_vec *color, t_hitRec *rec, t_ray *ray, t_scene *scene)
{
	if (rec->mat == MATTE_TYPE)
		lp_shade(color, rec, ray, scene);
	
}
