#ifndef RAY_H
# define RAY_H
# include "vector.h"

typedef struct s_ray
{
	t_vec	dir;
	t_vec	orig;
}	t_ray;

void	ray_at(t_vec *res, t_ray *ray, double t);

void	ray_fillRay(t_ray *ray, t_vec orig, t_vec dir);

#endif
