#include "vector.h"
#include "ray.h"
#include "stdlib.h"

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

void	ray_toStr(char	*string, t_ray *ray, int precision)
{
	std_assert(precision > 0);
	std_strlcpy(string, "orig ", 6);
	vec_toStr(string + std_strlen(string), &ray->orig, precision);
	std_strlcpy(string + std_strlen(string), " dir ", 6);
	vec_toStr(string + std_strlen(string), &ray->dir, precision);
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
