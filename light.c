#include "light.h"
# include "ray.h"
# include "vector.h"

void	light_rayToLight(t_ray *ray, t_vec *point, t_vec *src)
{
	ray->orig = *point;
	vec_subs(&ray->dir, src, point);
	vec_unitVector(&ray->dir, &ray->dir);
}
