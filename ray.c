#include "vector.h"
#include "ray.h"

void	ray_at(t_vec *res, t_ray *ray, double t)
{
	vec_scale(res, t, &(ray->dir));
	vec_add(res, &(ray->orig), res); 
}

void	ray_fillRay(t_ray *ray, t_vec orig, t_vec dir)
{
	ray->orig = orig;
	ray->dir = dir;
}
/*
int main()
{
	t_vec	orig;
	t_vec	dir;
	t_ray	ray;

	vec_fillVec(&orig, 1, 1, 1);
	vec_fillVec(&dir, 2, 2, 2);
	ray_fillRay(&ray, orig, dir);
}
*/
